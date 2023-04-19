#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define DIM 100


int main (int argc, char *argv[]) {
    if (argc < 4){
        perror("Numero insufficiente di parametri!");
        exit(1);
    }

    char dir1[DIM];
    char dir2[DIM];
    int num_files = argc-3;
    int pid, pidnipote, status, statusnipote;
    char miopid[20];
    char newname[20];

    strcpy(dir1, argv[1]);
    strcpy(dir2, argv[2]);

    

    for (int i=0; i < num_files; i++){
        pid = fork();
        if (pid < 0)
        {
            perror("Fork figlio fallita!");
            exit(1);

        } else if (pid == 0) //codice figlio
        {
            char fileI[DIM];
            strcpy(fileI, dir1);
            strcat(fileI, "/");
            strcat(fileI, argv[i+3]);

            pidnipote = fork();
            if (pidnipote < 0)
            {
                perror("Fork nipote fallita!");
                exit(1);
                
            } else if (pidnipote == 0) //codice nipote
            {
                execlp("/usr/bin/cp", "cp", fileI, dir2, (char *) 0);
                perror("cp fallita");
                exit(1);

            } else { //codice figlio(padre del nipote)
                wait(&statusnipote);
                if (WIFEXITED(statusnipote)) {
                    printf("Terminazione volontaria di %d [NIPOTE] con stato %d\n", pidnipote, WEXITSTATUS(statusnipote));
                    sprintf(miopid,"%d",getpid());
                    strcpy(newname, dir1);
                    strcat(newname, "/");
                    strcat(newname, miopid);

                    execlp("/usr/bin/mv", "mv", fileI, newname, (char *) 0);
                    perror("mv fallita");
                    exit(1);
                }
                else if (WIFSIGNALED(statusnipote)){
                    printf("Terminazione involontaria [NIPOTE] per segnale %d\n", WTERMSIG(statusnipote));
                }
            }
        } else { //codice padre
            wait(&status);
            if (WIFEXITED(status))
                    printf("Terminazione volontaria di %d [FIGLIO] con stato %d\n", pid, WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                    printf("Terminazione involontaria [FIGLIO] per segnale %d\n", WTERMSIG(status));
        }
        
        
    }
    return 0;

    
}
