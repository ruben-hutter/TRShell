#include "executor.h"

// searches a command in all directories listed in $PATH
char* search_path(char* command_name) {
    // get comma seperated list of directories
    char* PATH = getenv("PATH");
    // pointer to beginning of element
    char* entry_start = PATH;
    // pointer to end of element
    char* entry_end;

    // iterate through entries
    while (entry_start && *entry_start) {
        // both pointers at start of entry
        entry_end = entry_start;

        // move end pointer back until at end of entry
        while (*entry_end && *entry_end != ':') {
            entry_end++;
        }

        // get length of entry
        int entry_length = entry_end - entry_start;
        if (!entry_length) {
            entry_length = 1;
        }

        // get length of command
        int command_name_length = strlen(command_name);

        // prepare string to store path
        char path[entry_length+1+command_name_length+1];

        // copy entry to path
        strncpy(path, entry_start, entry_end-entry_start);
        path[entry_end-entry_start] = '\0';

        // if missing append / to end fo path
        if (entry_end[-1] != '/') {
            strcat(path, "/");
        }

        // append command name to path
        strcat(path, command_name);

        // check if file exists
        struct stat st;

        // exists
        if (stat(path, &st) == 0) {
            // exists
            if (!S_ISREG(st.st_mode)) {
                errno = ENOENT;

                // move pointers to start of next entry
                entry_start = entry_end;

                // if one char before first char of next entry -> move one forwad
                if (*entry_end == ':') {
                    entry_start++;
                }
                continue;
            }

            // malloc space for path
            entry_start = malloc(strlen(path)+1);
            if (!entry_start) {
                return NULL;
            }

            // copy path to malloced space and return
            strcpy(entry_start, path);
            return entry_start;            
        }

        // move pointers to start of next entry
        entry_start = entry_end;

        // if one char before first char of next entry -> move one forwad
        if (*entry_end == ':') {
            entry_start++;
        }
    }

    errno = ENOENT;
    return NULL;
}

// executes a command using exec v
int exec_command(int argc, char** argv) {

    // if starts with / -> assume its a path and try run directly
    if (strchr(argv[0], '/')) {
        execv(argv[0], argv);
        return 0;  
    }
    
    // search for command with that name
    char* path = search_path(argv[0]);

    // no command found -> return
    if (!path) {
        return 0;
    }

    // exec command
    execv(path, argv);
    free(path);
    return 0;
}

static inline void free_argv(int argc, char** argv) {
    if (!argc) {
        return;
    }

    while (argc--) {
        free(argv[argc]);
    }
}

int do_simple_command(struct tree_node* node) {
    if (!node) {
        return 0;
    }

    struct tree_node* child = node->first_child;
    if (!child) {
        return 0;
    }

    int argc = 0;
    long max_args = 255;
    char* argv[max_args+1];     // keep 1 for the terminating NULL arg
    char* str;

    while (child) {
        str = child->value.string;
        argv[argc] = malloc(strlen(str)+1);

        if (!argv[argc]) {
            free_argv(argc, argv);
            return 0;
        }

        strcpy(argv[argc], str);
        argc++;
        if (argc >= max_args) {
            break;
        }
        child = child->next_sibling;
    }
    argv[argc] = NULL;

    // check if command calls builtin function
    for(int iterator = 0; iterator < builtin_utility_count; iterator++) {
        if (strcmp(argv[0], builtin_utilities[iterator].name) == 0) {
            builtin_utilities[iterator].func(argc, argv);
            free_argv(argc, argv);
            return 1;
        }
    }

    pid_t child_pid = 0;
    if ((child_pid = fork()) == 0) {
        exec_command(argc, argv);
        fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
        if (errno == ENOEXEC) {
            exit(126);
        } else if (errno == ENOENT) {
            exit(127);
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (child_pid < 0) {
        fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
        return 0;
    }

    int status = 0;
    waitpid(child_pid, &status, 0);
    free_argv(argc, argv);

    return 1;
}
