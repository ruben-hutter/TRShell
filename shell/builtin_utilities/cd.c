#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <libgen.h> 
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TAM 1000 

int main(void) {

    char cad[TAM];             
    char *argv[TAM]; 
    char *gdir;
    char *dir;
    char *to;
    char buf[TAM];
    pid_t pid;
    int status;

    while (1) {                   

        printf("user@PC: ");    
        fgets(cad, 1000, stdin);

        // Si encontramos un salto de linea (se pulsa enter)
        if (cad[strlen(cad) - 1] == '\n')                                                           
            cad[strlen(cad) - 1] = '\0';    // lo marcamos como final de sentencia            



        // Exit para salir del shell
        if (!strcmp(argv[0], "exit")) exit(0);  

        if (!strcmp(argv[0], "cd")){
            chdir(to);
            continue;
        }            

        pid = fork();

        if (pid == 0) {   

            if (execvp(*argv, argv) < 0) {
                printf("%s: no se encontró la orden \n", argv[0]);
                exit(1);
            }
        } else {  
            waitpid(pid, &status, 0);
        }   
    }
    return 0;
}

void cd(int argc, char** argv) {
}