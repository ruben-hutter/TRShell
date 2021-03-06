#include "input_reader.h"

static struct termios old_settings;
int dump_buffer_flag = 0;

// reads user input from the stdin
char* read_from_input() {
    char temp_buffer[READ_BUFFER_SIZE];
    memset(temp_buffer, '\0', READ_BUFFER_SIZE * sizeof(char));
    char* buffer = NULL;
    char buffer_length = 0;

    set_tty_raw();

    while (get_string_from_input(temp_buffer, READ_BUFFER_SIZE)) {
        // get length of read input
        // ex. "ls -al" -> "ls -al\n" (without '\0')
        int temp_buffer_length = strlen(temp_buffer);
        // create buffer if not existing or expand to accomodate more input
        if (!buffer) {
            buffer = (char*) malloc(temp_buffer_length + 1);
        } else {
            // increase buffers allocated size
            char* new_buffer = (char*) realloc(buffer,
                                        buffer_length + temp_buffer_length + 1);
            // check for failed allocation
            if (new_buffer) {
                buffer = new_buffer;
            } else {
                free(buffer);
                buffer = NULL;
            }
        }

        // failed allocating buffer
        if (!buffer) { 
            printf("error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        // append temp_buffer to allocated buffer
        strcpy(buffer+buffer_length, temp_buffer);

        // last buffer char is "new line"
        if (temp_buffer[temp_buffer_length - 1] == '\n') {
            
            // only contains newline
            if (temp_buffer_length == 1) {
                void restore_old_tty_settings();
                return buffer;
            }

            // second last char wasn't a line-brake char
            if (temp_buffer[temp_buffer_length - 2] != '\\') {
                void restore_old_tty_settings();
                return buffer;
            }

            // if continues, remove newline and print multiline command prompt
            buffer[buffer_length+temp_buffer_length - 2] = '\0';
            temp_buffer_length -= 2;
            print_prompt_2();
        }

        buffer_length += temp_buffer_length;
    }
    void restore_old_tty_settings();
    return buffer;
}

// extracts the last input from buffer
int get_string_from_input(char* buffer, int buffer_size) {
    // init buffer indexes
    int buffer_position = 0;
    int buffer_end_position = 0;
    int* buff_pos_ptr = &buffer_position;
    int* buff_end_pos_ptr = &buffer_end_position;
    int current_char;

    memset(buffer, '\0', READ_BUFFER_SIZE * sizeof(char));
    
    // handle previous buffer dumped
    if (dump_buffer_flag) {
        // reset buffer dump flag
        dump_buffer_flag = 0;
        if (last_approach) {
            // move last approach to buffer
            set_buffer_to_string(last_approach, buffer, buff_pos_ptr,
                                    buff_end_pos_ptr);
            printf(last_approach);
        } 
    }

    // get chars from stdin
    while(current_char = getchar()) {
        // handel backspace
        if (current_char == TERMINAL_BACKSPACE) {
            handle_backspace(buffer, buff_pos_ptr, buff_end_pos_ptr);
            continue;
        }
        // handle tabs
        if (current_char == '\t') {
            char* result = autocomplete(buffer);
            if (!result) {
                // handle dump buffer flag
                if (dump_buffer_flag) {
                    return 0;
                }
                continue;
            }
            remove_line();
            print_prompt();
            set_buffer_to_string(result, buffer, buff_pos_ptr, buff_end_pos_ptr);
            printf(result);
            continue;
        }
        // hadle arrows
        if (current_char == '\033') {
            handle_arrow(buffer, buff_pos_ptr, buff_end_pos_ptr);
            continue;
        }
        // buffer full
        if (buffer_end_position == buffer_size) {
            return 1;
        }
        // handle enter
        if (current_char == '\n') {
            buffer[buffer_end_position++] = '\n';
            // eventually add terminator to buffer here!!!
            putchar('\n');
            return 1;
        }

        // handle insert
        if (buffer_position < buffer_end_position) {
            // shift buffer to accomodate new char
            shift_string_right(buffer, buffer_position, buffer_end_position);
            buffer_end_position++;
            // delete line right of cursor
            printf("\033[K");
            // add char to buffer
            buffer[buffer_position] = current_char;
            // print rest of string after insert
            put_string_section(buffer, buffer_position, buffer_end_position - 1);
            // reset cursor position
            printf("\033[%dD", buffer_end_position - buffer_position - 1);
            buffer_position++;
        } else {
            // add char to buffer
            buffer[buffer_position] = current_char;
            putchar(current_char);
            buffer_position++;
            buffer_end_position++;
        }
    }
}

// initiates the dump of the current line buffer
void dump_buffer() {
    dump_buffer_flag = 1;
}

// removes last char and updates buffer
void handle_backspace(char* buffer, int* buffer_position,
                        int* buffer_end_position) {
    if (*buffer_position < 1) {
        return;
    }
    // move cursor position to deltable character
    printf("\033[1D");
    // delete line right of cursor
    printf("\033[K");
    // move buffer position to deltable character
    (*buffer_position)--;
    // shift buffer to left to remove deletable char
    shift_string_left(buffer, *buffer_position, *buffer_end_position);
    // update buffer end position
    (*buffer_end_position)--;
    // print rest of buffer
    put_string_section(buffer, *(buffer_position), *(buffer_end_position) - 1);
    if (*(buffer_position) == (*buffer_end_position)) {
        return;
    }
    // reset cursor position
    printf("\033[%dD", *buffer_end_position - *buffer_position);
}

// hande control sequence
void handle_arrow(char* buffer, int* buff_pos_ptr, int* buff_end_pos_ptr) {
    if (getchar() == '[') {
        switch (getchar()) {
            case 'A':
                // up arrow
                char* previous_history_string = get_previous_history_entry_string();
                if (previous_history_string) {
                    remove_line();
                    print_prompt();
                    set_buffer_to_string(previous_history_string, buffer,
                                            buff_pos_ptr, buff_end_pos_ptr);
                    printf(buffer);
                }
                break;
            case 'B':
                // down arrow
                char* next_history_string = get_next_history_entry_string();
                if (next_history_string) {
                    remove_line();
                    print_prompt();
                    set_buffer_to_string(next_history_string, buffer,
                                            buff_pos_ptr, buff_end_pos_ptr);
                    printf(buffer);
                }
                break;
            case 'C':
                // right arrow
                if (*buff_pos_ptr >= *buff_end_pos_ptr) {
                    break;
                }
                printf("\033[1C");
                (*buff_pos_ptr)++;
                break;
            case 'D':
                // left arrow
                if (*buff_pos_ptr <= 0) {
                    break;
                }
                printf("\033[1D");
                (*buff_pos_ptr)--;
                break;
        }
    }
}

// erase line and reprint prompt
void remove_line() {
    // erase line
    printf("\033[2K");
    // move cursor to beginning of line
    printf("\033[0G");
}

// set buffer to entered string
void set_buffer_to_string(char* string, char* buffer, int* buff_pos_ptr,
                            int* buff_end_pos_ptr) {
    // string is null
    if (!string) {
        return;
    }
    // buffer is null
    if (!buffer) {
        return;
    }
    // set buffer to new string
    strcpy(buffer, string);
    cut_at_trailing_newline(buffer);

    // set end index to length of string without terminator or newline
    (*buff_end_pos_ptr) = strlen(buffer);
    // current position to append is also end of string
    (*buff_pos_ptr) = (*buff_end_pos_ptr);
}

// set tty mode to raw
void set_tty_raw() {
    static struct termios new_settings;
    // get old terminal settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // create copy of terminal settings
    new_settings = old_settings;
    // ICANON normally takes care that one line at a time will be processed
    // that means it will return if it sees a "\n" or an EOF or an EOL
    new_settings.c_lflag &= ~(ICANON);
    new_settings.c_lflag &= ~(ECHO);        
    // apply new settings to stdin
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

// restore the old settings
void restore_old_tty_settings() {
    tcsetattr( STDIN_FILENO, TCSANOW, &old_settings);
}
