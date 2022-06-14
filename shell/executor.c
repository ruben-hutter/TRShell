#include "executor.h"

// free all given string arguments
static inline void free_argv(int argc, char** argv) {
    if (!argc) {
        return;
    }
    while (argc--) {
        free(argv[argc]);
    }
}

// searches a command in all directories listed in PATH
char* search_path(char* command_name) {
    // get length of command
    int command_name_len = strlen(command_name);
    // get comma seperated list of directories
    char* env_path = get_local_table_entry_value("PATH");
    char* env_path_cpy = get_malloced_copy(env_path);
    char* delimiter = ":";
    // single entry of local table path
    char* entry = strtok(env_path_cpy, delimiter);
    int entry_len = 0;
    while (entry != NULL) {
        entry_len = strlen(entry);
        // path of entry with space for slash, command and terminator
        char path[entry_len + command_name_len + 2];
        // put everything into path
        strcpy(path, entry);
        path[entry_len] = '/';
        strncpy(path + entry_len + 1, command_name, command_name_len);
        path[entry_len + command_name_len + 1] = '\0';
        // check if file exists
        struct stat st;
        if (stat(path, &st) == 0) {
            // exists
            if (!S_ISREG(st.st_mode)) {
                errno = ENOENT;
                continue;
            }
            // malloc space for path
            char* m_path = get_malloced_copy(path);
            if (!m_path) {
                free(env_path_cpy);
                return NULL;
            }
            free(env_path_cpy);
            return m_path;            
        }
        entry = strtok(NULL, delimiter);
    }
    free(env_path_cpy);
    errno = ENOENT;
    return NULL;
}

// executes a command using execv
int exec_command(int argc, char** argv) {
    // if starts with / -> assume its a path and try run directly
    if (strchr(argv[0], '/')) {
        execv(argv[0], argv);
        return 0;  
    }
    // search for command with that name
    char* path = search_path(argv[0]);

    if (!path) {
        return 0;
    }
    // exec command
    execv(path, argv);
    free(path);
    return 0;
}

// execute a simple command
int do_simple_command(struct tree_node* node) {
    if (!node) {
        return 1;
    }

    struct tree_node* child = node->first_child;
    if (!child) {
        return 0;
    }

    int argc = 0;
    long max_args = 255;
    char* argv[max_args + 1];     // keep 1 for the terminating NULL arg
    char* str;
    // add every child as an array entry
    while (child) {
        str = child->value.string;
        argv[argc] = get_malloced_copy(str);
        if (!argv[argc]) {
            free_argv(argc, argv);
            return 1;
        }
        // increment counter
        argc++;
        if (argc >= max_args) {
            break;
        }
        child = child->next_sibling;
    }
    argv[argc] = NULL;

    // check if command calls builtin function
    for (int iterator = 0; iterator < builtin_utility_count; iterator++) {
        if (strcmp(argv[0], builtin_utilities[iterator].name) == 0) {
            builtin_utilities[iterator].func(argc, argv);
            free_argv(argc, argv);
            return 0;
        }
    }

    // let a subprocess execute the command
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
        return 1;
    }
    // wait for the command to be executed,
    // and return an error code if command failed
    int status = 0;
    waitpid(child_pid, &status, 0);
    free_argv(argc, argv);
    return 0;
}
