#ifndef COLORS_H
#define COLORS_H

// colors used for normal users
#define USER_PRIMARY "\033[38;5;35m"
#define USER_SECONDARY "\033[38;5;38m"

// colors used for root
#define ROOT_PRIMARY "\033[38;5;196m"
#define ROOT_SECONDARY "\033[38;5;202m"

// miscellaneous style information
#define STYLE_BOLD "\033[1m"
#define COLOR_WHITE "\033[38;5;15m"
#define STYLE_RESET "\033[0m"

// concat input_strings with style reset character at the appendet to the end
void concatenate_with_style(int num_of_input_strings, char* styled_string, ...);
// get the length of all passed string concatenated with the style reset char apendet to the end
int get_concatenated_length_with_style(int num_of_input_strings, ...);
#endif