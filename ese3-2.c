#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

#define MAX_CHILDREN 255
int pid[MAX_CHILDREN];
char command[20];
int num = 0;
int status;
int figli_terminati = 0;
char var[20];
int pidnipote = 0;

void gestore_nipote(int signum){
    printf("Comando %s eseguito correttamente!\n", command);
    fflush(stdout);
    //kill(pidnipote, SIGKILL);
    kill(getpid(), SIGKILL);
    return;
}

void gestore_figli(int signum){
    //gestione dei figli
    printf("Finito!\n");
    int pidF = 0;
    for (int counter = 0; counter < 2; counter++){
        pidF = pid[counter];
        kill(pidF, SIGKILL);
    }
    exit(EXIT_SUCCESS);
}

void gestore_exec(int signum) {

    pidnipote = fork();

    if((pidnipote >0)){
        signal(SIGCHLD, gestore_nipote);
    }else if(pidnipote == 0){
        printf("P3: Segnale ricevuto (%d), eseguo il comando [%s]\n",signum, command);
        strcpy(var, "/usr/bin/");
        strcat(var, command);

        execlp(var, command, (char *) 0);
        perror("Execl fallita!");
        exit(EXIT_FAILURE);
    }else{
        perror("Fork nipote fallita!");
        exit(EXIT_FAILURE);
    }

}

void gestore_timeout(int signum) {
    printf("Timeout scaduto!\n");
    int pidF2 = 0;
    for (int counter2 = 0; counter2 < 2; counter2++){
        pidF2 = pid[counter2];
        kill(pidF2, SIGKILL);
    }
    exit(EXIT_SUCCESS);
}

void gestore_wait(int signum) {
    figli_terminati++;

    if(figli_terminati == 2){
        printf("Figli terminati!\n");
        exit(EXIT_SUCCESS);
    }
    
    return;
}






int main (int argc, char* argv[]){

    if (argc != 3) {
        perror("Errore nel numero di argomenti\n");
        exit(EXIT_FAILURE);
    }

    num = atoi(argv[2]); //copia T in variabile
    strcpy(command, argv[1]); //copia comando nell'array

    for(int i=0; i < 2; i++){
        pid[i] = fork();
        if (pid[i] < 0){ //Errore nella fork

            perror("Fork fallita!");
            exit(EXIT_FAILURE);

        } else if(pid[i] == 0){
            if(i == 0){ //P1

                signal(SIGUSR2, gestore_exec);
                int j = 0;
                for(;;){
                    printf("P1: Stampo radici dei numeri: %6F\n\n",sqrt(j));
                    j++;
                    sleep(1);
                }
                
            }else{ //P2
                sleep(3);
                int pidp2 = getpid();

                if((pidp2 % 2) == 0){ //pid pari
                    printf("\n\n[PID pari]\n");
                    kill(getppid(), SIGUSR1);
                    exit(EXIT_SUCCESS);

                }else{ //pid dispari
                    printf("\n\n[PID dispari]\n");
                    kill(pid[0], SIGUSR2);
                    exit(EXIT_SUCCESS);

                }
            }
        }else {
            //PADRE
            signal(SIGUSR1, gestore_figli);
            signal(SIGALRM, gestore_timeout);
            signal(SIGCHLD, gestore_wait);

            if(i == 1){
                int tempo;
                tempo = alarm(num);
                int k=0;
                for(;;){

                    printf("PADRE: Stampo potenze di 2: %6F\n\n", pow(2, k));
                    k++;
                    sleep(1);

                }
            }

            
        }
    }

    return 0;
}