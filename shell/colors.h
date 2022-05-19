#ifndef COLORS_H
#define COLORS_H

#define ORANGE "\033[38;5;202m"
#define GREEN "\033[38;5;154m"
#define BOLD "\033[1m"
#define WHITE "\033[38;5;15m"
#define RESET "\033[0m"

char* colorize(char* string, char* color);

char* get_malloc_empty_string(int length);

#endif