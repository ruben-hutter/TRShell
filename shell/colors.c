# include <string.h>
# include <stdlib.h>
#include <stdarg.h>

# include "colors.h"
# include "string_utils.h"

void apply_style(int num_of_style_infos, char* raw_string, char* styled_string, char* style_info, ...) {
    // prepare arg list for iteration
    va_list style_args;
    va_start(style_args, num_of_style_infos);
    // concate style info
    v_concatenate(num_of_style_infos, styled_string, style_args);
    va_end(style_args);
    // add raw string
    strcat(styled_string, raw_string);
    strcat(styled_string, STYLE_RESET);
}
