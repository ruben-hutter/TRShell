# include "colors.h"

// concat input_strings with style reset character at the appendet to the end
void concatenate_with_style(int num_of_input_strings, char* styled_string, ...) {
    // prepare arg list for iteration
    va_list input_args;
    va_start(input_args, styled_string);
    // concate style info
    v_concatenate(num_of_input_strings, styled_string, input_args);
    va_end(input_args);
    // add raw string
    strcat(styled_string, STYLE_RESET);
}

// get the length of all passed strings concatenated
// with the style reset char apendet to the end
int get_concatenated_length_with_style(int num_of_input_strings, ...) {
    // prepare arg list for iteration
    va_list input_args;
    va_start(input_args, num_of_input_strings);
    int concatenated_length = v_get_concatenated_length(num_of_input_strings,
                                                        input_args);
    va_end(input_args);
    concatenated_length += strlen(STYLE_RESET);
    return concatenated_length;
}
