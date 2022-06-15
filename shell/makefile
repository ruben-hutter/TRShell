all:
	gcc command_tree.c shell.c buffered_string.c autocomplete.c history.c prompt.c colors.c string_utils.c executor.c token.c input_reader.c symbol_table.c init.c builtin_utilities/exit.c builtin_utilities/clera.c builtin_utilities.c builtin_utilities/ht.c builtin_utilities/dump.c builtin_utilities/builtins.c builtin_utilities/cd.c -o trshell.o

# run this to compile the shell
new_all: trshell

trshell: shell.o output.o utils.o input.o executor.o debug.o structures.o
	gcc -o trshell shell.o output.o utils.o input.o executor.o debug.o structures.o

shell.o: shell.c shell.h
	gcc -c shell.c

output.o: prompt.o colors.o
	gcc -c prompt.o colors.o

prompt.o: prompt.c prompt.h
	gcc -c prompt.c

colors.o: colors.c colors.h
	gcc -c colors.c

executor.o: executor.c executor.h
	gcc -c executor.c

utils.o: builtin_utilities.o string_utils.o init.o token.o 
	gcc -o utils.o builtin_utilities.o string_utils.o init.o token.o 

builtin_utilities.o: builtin_utilities.c builtin_utilities.h
	gcc -c builtin_utilities.c

string_utils.o: string_utils.c string_utils.h
	gcc -c string_utils.c

init.o: init.c init.h
	gcc -c init.c

token.o: token.c token.h
	gcc -c token.c

structures.o: command_tree.o symbol_table.o
	gcc -c command_tree.o symbol_table.o

command_tree.o: command_tree.c command_tree.h
	gcc -c command_tree.c

symbol_table.o: symbol_table.c symbol_table.h
	gcc -c symbol_table.c

input.o: buffered_string.o input_reader.o
	gcc -o input.o buffered_string.o input_reader.o

buffered_string.o: buffered_string.c buffered_string.h
	gcc -c buffered_string.c

input_reader.o: input_reader.c input_reader.h
	gcc -c input_reader.c

debug.o: dump.c dump.h
	gcc -o debug.o dump.c

clean:
	rm *.o
	rm trshell
