#include "input_reader.h"

// reads user input from the stdin
char* read_from_input() {
    char temp_buffer[READ_BUFFER_SIZE];
    char* buffer = NULL;
    char buffer_length = 0;

    while (fgets(temp_buffer, READ_BUFFER_SIZE, stdin)) {

        // check if input is control sequence
        if (is_control_sequence(temp_buffer)) {
            handle_control_sequence(temp_buffer);
        }
        
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
                return buffer;
            }

            if (temp_buffer[temp_buffer_length-2] != '\\') {
                return buffer;
            }

            // if it continues remove newline and print multiline command input prompt
            buffer[buffer_length+temp_buffer_length-2] = '\0';
            temp_buffer_length -= 2;
            print_prompt_2();
        }

        buffer_length += temp_buffer_length;
    }

    return buffer;
}

// checks if character tripple is a control sequence
int is_control_sequence(char* sequence) {
    int length = strlen(sequence);
    for (int pos = 0; pos < length; pos++) {
        if (sequence[pos] == '\033' & sequence[pos + 1] == '[') {
            return true;
        }
    }
    return false;
}

// hande control sequence
void handle_control_sequence(char* sequence) {
    // find posiiton of sequence
    int length = strlen(sequence);
    int pos;
    for (pos = 0; pos < length-2; pos++) {
        if (sequence[pos] == '\033' & sequence[pos + 1] == '[') {
            break;
        }
    }
    // interpret sequence
    switch (sequence[pos + 2])
    {
    case 'A':
        // up arrow pressed
        printf("UP_ARROW");
        break;
    case 'B':
        // down arrow pressed
        printf("DOWN_ARROW");
        break;
    default:
        break;
    }
}