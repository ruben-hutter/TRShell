#ifndef COLORS_H
#define COLORS_H

#define PRIMARY "\033[38;5;35m"
#define SECONDARY "\033[38;5;38m"
#define BOLD "\033[1m"
#define WHITE "\033[38;5;15m"
#define RESET "\033[0m"

char* colorize(char* string, char* color);

char* style(char* string, char* style);

char* get_malloc_empty_string(int length);

#endif