#include "input_reader.h"

static struct termios old_settings;

// reads user input from the stdin
char* read_from_input() {
    char temp_buffer[READ_BUFFER_SIZE];
    char* buffer = NULL;
    char buffer_length = 0;

    set_tty_raw();

    while (get_string_from_input(temp_buffer, READ_BUFFER_SIZE)/*fgets(temp_buffer, READ_BUFFER_SIZE, stdin)*/) {
        
        // get length of read input
        int temp_buffer_length = strlen(temp_buffer); // ex. "ls -al" -> "ls -al\n" (without '\0')

        // create buffer if not existing or expand to accomodate more input
        if (!buffer) {
            buffer = malloc(temp_buffer_length+1);
        } else {
            // increase buffers allocated size
            char *new_buffer = realloc(buffer, buffer_length+temp_buffer_length+1);
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
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        // append temp_buffer to allocated buffer
        strcpy(buffer+buffer_length, temp_buffer);

        // last buffer char is "new line"
        if (temp_buffer[temp_buffer_length-1] == '\n') {
            
            // only contains newline
            if (temp_buffer_length == 1) {
                void restore_old_tty_settings();
                return buffer;
            }

            if (temp_buffer[temp_buffer_length-2] != '\\') {
                void restore_old_tty_settings();
                return buffer;
            }

            // if it continues remove newline and print multiline command input prompt
            buffer[buffer_length+temp_buffer_length-2] = '\0';
            temp_buffer_length -= 2;
            print_prompt_2();
        }

        buffer_length += temp_buffer_length;
    }
    void restore_old_tty_settings();
    return buffer;
}

int get_string_from_input(char* buffer, int buffer_size) {
    int buffer_position = 0;
    int* buff_pos_ptr = &buffer_position;
    int current_char;
    // get chars from stdin
    while(current_char = getchar()) {
        // handel backspace
        if (current_char == TERMINAL_BACKSPACE) {
            handle_backspace(buff_pos_ptr);
            continue;
        }
        // handle tabs
        /*if (current_char == '\t') {
            handle_tabs(&buffer_position);
            continue;
        }*/
        // handle arrows


        // buffer full
        if (buffer_position == buffer_size) {
            return 1;
        }
        // fix underflown buffer
        if (buffer_position < 0) {
            buffer_position = 0;
        }
        // add char to buffer
        buffer[buffer_position] = current_char;
        buffer_position++;
        // handle newline
        if (current_char == '\n') {
            buffer[buffer_position++] = '\n';
            buffer[buffer_position] = '\0';
            return 1;
        }
    }
}

// removes carret notation backspace from terminal and updates buffer pointer
void handle_backspace(int* buffer_position) {
    // handle backspace on empty line
    if (*buffer_position == 0) {
        printf("\033[2D\033[0K");
        return;
    }
    // handle normal backspace
    if (*buffer_position > 0) {
        printf("\033[3D\033[0K");
        (*buffer_position)--;
        return;
    }
}

// remove tabs from
void handle_tabs(int* buffer_position) {
    // handle tab on empty line
    if (*buffer_position == 0) {
        printf("\033[2D\033[0K");
    }
    // handle normal tab
    if (*buffer_position > 0) {
        printf("\033[6D\033[0K");
        *buffer_position--;
    }
}

// hande control sequence
void handle_arrow(char* sequence) {
    //TODO: implementation
}

/*set tty mode to raw*/
void set_tty_raw() {
    static struct termios new_settings;
    // get old terminal settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // create copy of terminal settings
    new_settings = old_settings;
    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    new_settings.c_lflag &= ~(ICANON);          
    // apply new settings to stdin
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

/*restore the old settings*/
void restore_old_tty_settings() {
    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &old_settings);
}

/*
/*This is your part:
    I choose 'e' to end input. Notice that EOF is also turned off
    in the non-canonical mode
    char input[1024];
    input[0] = '\0';
    int counter = 0;
    while((c=getchar())!= 'e') {
        if (c == 0x7F) {
            printf("\b\b\b   \b\b\b");
            counter--;
            continue;
        }
        input[counter++] = c;
        if (c == '\n') {
            input[counter++] = '\n';
            input[counter] = '\0';
            printf(input);
            counter = 0;
            input[0] == '\0';
        }
    } 
*/