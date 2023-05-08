#!/bin/bash

if [[ $# -lt 4 ]]
    then echo "Non abbastanza argomenti!"; exit 1;
fi

case "$3" in 
/*)
    if [[ -f $3 ]]
        then echo "Il file esiste già!"; exit 2;
        else > "$3"
    fi
    ;;
*) 
    echo "$3 non è un nome assoluto"; exit 3;
    ;;
esac

if ! [[ $2 =~ ^[0-9]+$ ]] ; then
    echo "$2 non è un intero positivo" 
    exit 2
fi


G=$1
N=$2
OutFile=$3

shift
shift
shift

for dir in "$@"
do
    case "$dir" in
    /*)
        if ! [[ -d "$dir" ]]
            then echo "La directory non esiste"; exit 3
        fi
        ;;
    *)
        echo "La directory non è in formato assoluto"; exit 4
        ;;
    esac
done

if  [[ "$0" = /* ]] 
    then
        dir_name=`dirname "$0"`
        recursive_cmd="$dir_name/ese7-2-recurse.sh"

elif [[ "$0" = */* ]]
    then
        dir_name=`dirname "$0"`
        recursive_cmd="`pwd`/$dir_name/ese7-2-recurse.sh"

    else
        recursive_cmd=ese7-2-recurse.sh
        
fi

for dir in $@
do
    "$recursive_cmd" "$G" "$N" "$OutFile" "$dir"
done

echo  "Sono stati trovati `cat "$OutFile" | wc -l` files"
