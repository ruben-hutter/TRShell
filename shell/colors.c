# include "colors.h"
#include <string.h>

// wrap the passed string into the specified color 
char* colorize(char* string, char* color) {
    return strcat(strcat(color, color), COLOR_RESET);
}

//