#ifndef COLORS_H
#define COLORS_H

// colors used for normal users
#define USER_PRIMARY "\033[38;5;35m"
#define USER_SECONDARY "\033[38;5;38m"

// colors used for root
#define ROOT_PRIMARY "\033[38;5;35m"
#define ROOT_SECONDARY "\033[38;5;38m"

// miscellaneous style information
#define BOLD "\033[1m"
#define WHITE "\033[38;5;15m"
#define STYLE_RESET "\033[0m"

void apply_style(int num_of_style_infos, char* raw_string, char* styled_string, char* style_info, ...);

#endif