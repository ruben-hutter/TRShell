# include "colors.h"
# include <string.h>
# include <stdlib.h>

// wrap the passed string into the specified color 
char* colorize(char* string, char* color) {
    int length= strlen(color)+strlen(string)+strlen(RESET);
    char* colored_string = get_malloc_empty_string(length);

    strcat(colored_string, color);
    strcat(colored_string, string);
    strcat(colored_string, RESET);

    return colored_string;
}

// prepend style data infront of string
char* style(char* string, char* style) {
    int length= strlen(style)+strlen(string)+strlen(RESET);
    char* styled_string = get_malloc_empty_string(length);

    strcat(styled_string, style);
    strcat(styled_string, string);
    strcat(styled_string, RESET);

    return styled_string;
}

char* get_malloc_empty_string(int length) {
    char* colored_string = malloc(length);
    *colored_string = '\0';
    return colored_string;
}
