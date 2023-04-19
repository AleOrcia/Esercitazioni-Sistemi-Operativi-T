#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NP 8 // al massimo 8 pipe -> 8 figli
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

        char buflettura;
        int X = 0;

        while ((read(pp[0], &buflettura, 1)) > 0)
        {
            if(buflettura == '\n'){
                X++;
            }
        }

        printf("Il file %s contiene %d righe che iniziano per %c\n", FileName, X, Car);

        close(pp[0]);

        exit(EXIT_SUCCESS);
        
        
    }else if(!pid){
        //figlio
        close(pp[0]);
       
    if((fd = open(FileName, O_RDONLY))< 0){
        perror("Errore nell'apertura file!\n");
    }
    char buff;
    int i = 0;
    char buff2;

    while ((read(fd, &buff, 1)) > 0)
    {
        if(buff == Car && i == 0){
            i++;
            write(pp[1], &buff, 1);

            while ((read(fd, &buff2, 1)) > 0)
            {
                write(pp[1], &buff2, 1);

                if(buff2 == '\n'){
                    break;
                }
                
            }
            
        }
        if(buff == '\n'){
                    i = 0;
                }
        
    }
    

    close(fd);
    close(pp[1]);
    
    exit(EXIT_SUCCESS);

    }else{
        perror("Fork error!\n");
    }


    return 0;
}
