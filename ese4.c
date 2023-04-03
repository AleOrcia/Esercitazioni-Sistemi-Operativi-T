#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DIM 25

typedef struct{
    int tipo;
    int quant;
} operazione;


int main (int argc, char *argv[]){

    if (argc != 4){
        perror("Numero argomenti errato!");
        exit(EXIT_FAILURE);
    }

    char Fin[DIM] = "";
    char Fprodotti[DIM] = "";
    char Fvendite[DIM] = "";

    strcpy(Fin, argv[1]);
    strcpy(Fprodotti, argv[2]);
    strcpy(Fvendite, argv[3]);

    int fd, n;
    char buff;


    fd = open(Fin, O_RDONLY);
    if(fd < 0){
        perror("Errore nell'apertura del file testuale\n");
        exit(EXIT_FAILURE);
    }

    int fd1 = creat(Fprodotti, 0777);
    int fd2 = creat(Fvendite, 0777);

    int i = 0;
    operazione V;
    operazione P;
    char temp[DIM] = "";

    char tipo[DIM] = "";
    char quant[DIM] = "";
    char tipo_operazione;
    int counter = 0;

    while((n = read(fd, &buff, 1)) > 0){
        
        if(buff != '\n'){ //prima del fine riga
            temp[counter] = buff;
            counter++;
        }else{ //arrivato al fine riga
            int k = 0;
            int counter2 = 0;
            int counter3 = 0;
            
            for(int j = 0; j < counter; j++){
                if (temp[j] != ',' && k == 0){
                    tipo[counter2] = temp[j];
                    counter2++;
            
                }else if (temp[j] != ',' && k == 1){
                    
                    quant[counter3] = temp[j];
                    counter3++;
                    
                }else if (temp[j] != ',' && k == 2 && temp[j] != '\n'){
                    tipo_operazione = temp[j];

                    if(tipo_operazione == 'V'){
                        V.tipo = atoi(tipo);
                        V.quant = atoi(quant);
                        write(fd2, &V, sizeof(operazione));

                    }else if(tipo_operazione == 'P'){
                        P.tipo = atoi(tipo);
                        P.quant = atoi(quant);
                        write(fd1, &P, sizeof(operazione));


                    }else{
                        perror("FileIn formattato male!");
                        printf("temp %c\n", temp[j]);
                    }

                }else if (temp[j] == ','){
                    k++;
                }
            }
            counter = 0;
        }
        
    }

    close(fd);
    close(fd1);
    close(fd2);

    return 0;
}