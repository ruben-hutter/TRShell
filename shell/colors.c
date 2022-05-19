# include "colors.h"
# include <string.h>
# include <stdlib.h>

// wrap the passed string into the specified color 
char* colorize(char* string, char* color) {
    int length= strlen(color)+strlen(string)+strlen(COLOR_RESET);
    char* colored_string = get_malloc_empty_string(length);

    strcat(colored_string, color);
    strcat(colored_string, string);
    strcat(colored_string, COLOR_RESET);

    return colored_string;
}

char* get_malloc_empty_string(int length) {
    char* colored_string = malloc(length);
    *colored_string = '\0';
    return colored_string;
}
