#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){

    if (argc < 4)
    {
        perror("Numero argomenti insufficiente!");
        exit(111);
    }
    
    int num_figli = argc -3;
    int pid = 0;
    int status;

    for (size_t i = 0; i < num_figli; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Fork fallita malamentemente");
            exit(1);
        }else if (pid == 0)
        {
            int pidfiglio = getpid();
            char fileI[100];
                strcpy(fileI, argv[1]);
                strcat(fileI, "/");
                strcat(fileI, argv[i+3]);

            if ((pidfiglio%2) == 0) //PID PARI
            {

                execlp("/usr/bin/cp", "cp", fileI, argv[2], (char *) 0);
                perror("Execl fallita! (cp)");
                exit(1);
            } else { //PID DISPARI
                execlp("/usr/bin/rm", "rm", fileI, (char *) 0);
                perror("Execl fallita! (rm)");
                exit(1);
            }
            
            

        } else if (pid > 0)
        {
            wait(&status);
            if (WIFSIGNALED(status))
                printf("Terminazione involontaria del processo [%d]\n", pid);

        }
        
        
        
    }

    execl("/usr/bin/ls", "ls", "-l", argv[2], (char *) 0);
    return 0;
    
    
}
