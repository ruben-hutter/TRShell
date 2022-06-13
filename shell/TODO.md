# Project TODO list

[] comment all code meaningfully
[] man page to builtin_utils
[] list builtin_utils

## Tobi

## Ruben

[~] makefile refactor
[] tilde for path change
[~] string manip
[x] string_between_char(char* string, char delimiter) [string_utils]
[] autocomplete -> get_binaries() refactor with strtok
[] executor -> search_path() refactor with strtok

---

apr = cd os/proj/trsh\ shell/shell\ s
apr = cd os/proj/"trsh shell"/"shell s
apr = cd "os/proj/trsh shell/shell s

tobi: char* string_to_change
ru: string mod on string_to_change
return void

pre: all before path [cd ]
path: all after pre, before approach [os/proj/trsh\ shell/]; [os/proj/"trsh shell"/]; [os/proj/trsh shell/]
n_complete: [shell\ s]; [shell s] -> ohne \, ohne " ['shell s']

pre + path + match
