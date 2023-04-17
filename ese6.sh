#!/bin/bash

if [ $# -ne 1 ]
then 
    echo Sintassi!
    exit
fi

echo "Scrivi un intero positivo: "
read N 

if [[ $N =~ ^[0-9]+$ && $N -gt 0 ]]
then echo OK!
else echo "Errore! Numero in input minore di 0!"; exit
fi

if [[ -f $1 ]]
then echo OK!
else echo "Errore! File fornito inesistente"; exit
fi

if [[ "$1" = /* ]]
then echo OK!
else echo "Errore! Non è stata fornita una path assoluta"; exit
fi

if [[ -r $1 ]]
then echo OK!
else echo "Errore! File senza permessi di lettura"; exit
fi


tail -n $N $1 | sort -r > "$HOME/result_$USER.out"
