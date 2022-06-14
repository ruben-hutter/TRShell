# Project TODO list

[] comment all code meaningfully
[] man page to builtin_utils
[] list builtin_utils

## Tobi

## Ruben

[~] makefile refactor
[] tilde for path change
[] autocomplete -> get_binaries() refactor with strtok
[] executor -> search_path() refactor with strtok

tobi ● operating_systems$ cd t==7221== Conditional jump or move depends on uninitialised value(s)
==7221==    at 0x10AB4E: querry_directories (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AA9D: autocomplete (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E898: get_string_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E791: read_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10A730: main (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==  Uninitialised value was created by a heap allocation
==7221==    at 0x4845899: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==7221==    by 0x10B95E: auto_string_manip (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AB3E: querry_directories (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AA9D: autocomplete (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E898: get_string_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E791: read_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10A730: main (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221== 
==7221== Conditional jump or move depends on uninitialised value(s)
==7221==    at 0x10BC52: free_approach_split (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AC40: querry_directories (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AA9D: autocomplete (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E898: get_string_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E791: read_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10A730: main (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==  Uninitialised value was created by a heap allocation
==7221==    at 0x4845899: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==7221==    by 0x10B95E: auto_string_manip (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AB3E: querry_directories (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10AA9D: autocomplete (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E898: get_string_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10E791: read_from_input (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
==7221==    by 0x10A730: main (in /home/tobi/uni_basel/operating_systems/TRShell/shell/trshell.o)
