#include<stdio.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO


int main(void){   
    int c;   
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*This is your part:
    I choose 'e' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
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
                        

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);


    return 0;
}