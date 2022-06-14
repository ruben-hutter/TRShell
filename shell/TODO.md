# Project TODO list

[~] comment all code meaningfully
[] man page to builtin_utils
[] list builtin_utils

## Tobi

## Ruben

[~] makefile refactor
[] tilde for path change
[x] autocomplete -> get_binaries() refactor with strtok
[] executor -> search_path() refactor with strtok
[] complete logo

---

// searches a command in all directories listed in $PATH
char* search_path(char* command_name) {
    // get length of command
    int command_name_len = strlen(command_name);
    // get comma seperated list of directories
    char* env_path = get_local_table_entry_value("PATH");
    char* delimiter = ":";
    // single entry of local table path
    char* entry = strtok(env_path, delimiter);
    int entry_len = 0;
    while (entry != NULL) {
        entry_len = strlen(entry);
        // path of entry with space for slash, command and terminator
        char path[entry_len + command_name_len + 2];
        // put everything into path
        strcpy(path, entry);
        path[entry_len] = '/';
        strncpy(path + entry_len + 1, command_name, command_name_len);
        path[entry_len + command_name_len + 2] = '\0';
        printf("path: %s\n", path);
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
                return NULL;
            }
            return m_path;            
        }
        entry = strtok(NULL, delimiter);
    }
    errno = ENOENT;
    return NULL;
}
