#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAXS 256

int main(int argc, char *argv[]){  //Il programma deve stampare sullo standard output il numero
                                   //di righe di FileName che iniziano per Car
    
    int N, pid, fd;
    char FileName[MAXS];
    char Car;
    int pp[2];
    int fdpipe;

    if (argc<3){ // almeno 2 argomenti
        printf("Numero argomenti sbagliato!\n");
        exit(-1);
    }  

    N = argc-1; 
    strcpy(FileName, argv[1]);
    Car = argv[2][0];
    pipe(pp);
    if(pp < 0){
        perror("Impossibile aprire la pipe!\n");
    }
    pid = fork();

    if(pid > 0){
        //padre
        close(pp[1]);
        close(0);
        dup(pp[0]);
        close(pp[0]);
        
        execl("/usr/bin/wc", "wc", "-l", (char*)0);
        perror("Execl padre!");
        exit(EXIT_FAILURE);
        
        
    }else if(!pid){
        //figlio
        close(pp[0]);
        close(1);
        dup(pp[1]);
        close(pp[1]);
       
    if((fd = open(FileName, O_RDONLY))< 0){
        perror("Errore nell'apertura file!\n");
    }
    char comm[3];
    comm[0] = '^';
    comm[1] = Car;
    comm[2] = '\0';

    execlp("/usr/bin/grep", "grep", comm, FileName, (char*)0);
    perror("Exec error!\n");
    exit(EXIT_FAILURE);
    
    }else{
        perror("Fork error!\n");
    }


    return 0;
}
