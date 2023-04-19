#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define DIM 25
#define NUMFIGLI 2

typedef struct{
int tipo;
int quant;
}operazione;

int pid1, pid2;
int fd, fd2;
int tp = 0;
int tv = 0;
int crtTempProd, crtTempVend;


operazione vend, prod;

void wait_child(){
    int status;
    int pid_terminated = wait(&status);
    if ((char)status==0 && ((status>>8)!=0) )
        printf("P0: figlio con PID=%d term. volontariamente con stato %d.\n",pid_terminated, status>>8);
    else if ((char)status!=0)
        printf("P0: figlio con PID=%d terminato involontariamente per segnale %d\n",pid_terminated,(char)status);
}

int main(int argc, char *argv[]){

    if (argc != 3){
        perror("Il numero dei parametri non è corretto!");
        exit(EXIT_FAILURE);
    }

    char Fprodotti[DIM];
    char Fvendite[DIM];

    strcpy(Fprodotti, argv[1]);
    strcpy(Fvendite, argv[2]);

    pid1 = fork();

    if(pid1 == 0){
        //figlio P1
        if((fd = open(Fprodotti, O_RDONLY))< 0){
            perror("Errore nell'apertura del file");
            exit(EXIT_FAILURE);
        }
        lseek(fd, -sizeof(operazione), SEEK_END);


        do{
            read(fd, &prod, sizeof(operazione));
            tp += prod.quant;
        }while ((lseek(fd,-2*sizeof(operazione), SEEK_CUR))>=0);

        int dimensione = snprintf( NULL, 0, "%d", tp );
        char buffer[dimensione+1];

        sprintf(buffer, "%d", tp);

        crtTempProd = creat("tempProd", 0777);
        if(crtTempProd < 0) {
            perror("Impossibile creare il file 'tempProd'");
            exit(EXIT_FAILURE);
        }

        int wrt = 0;
        if((wrt = write(crtTempProd, buffer, dimensione))< 0){
            perror("Impossibile aprire il file 'tempProd'");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);

    }else if(pid1 > 0){
        //padre
        pid2 = fork();
        
        if(pid2 == 0){
            //figlio P2
            if((fd2 = open(Fvendite, O_RDONLY))< 0){
            perror("Errore nell'apertura del file");
            exit(EXIT_FAILURE);
            }

            while ((read(fd2, &vend, sizeof(operazione)))>0){
            
                tv += vend.quant;
            }

            int dimensione2 = snprintf( NULL, 0, "%d", tv );
            char buffer2[dimensione2+1];

            sprintf(buffer2, "%d", tv);

            crtTempVend = creat("tempVend", 0777);
            if(crtTempVend < 0) {
                perror("Impossibile creare il file 'tempVend'");
                exit(EXIT_FAILURE);
            }

            int wrt2 = 0;
            if((wrt2 = write(crtTempVend, buffer2, dimensione2))< 0){
                perror("Impossibile aprire il file 'tempVend'");
                exit(EXIT_FAILURE);
            }
                exit(EXIT_SUCCESS);

        }else if(pid2 > 0){

            wait_child();

            if(tp >= tv){

                printf("I pezzi prodotti sono più di quelli venduti.\n");

            }else if(tp < tv){
                printf("I pezzi prodotti sono meno di quelli venduti.\n");
            }

        }else if(pid2 < 0){
            perror("Fork di P2 fallita!");
            exit(EXIT_FAILURE);
        }

    }else{
        perror("Fork di P1 fallita!");
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    close(fd2);
    close(crtTempProd);
    close(crtTempVend);

    return 0;

}
