#!/bin/bash

group=$1
N=$2
OutFile=$3
dir=$4

cd "$dir"

for i in `ls`
do
    if test -f "$i" -a -r "$i" #$file è un file ordinario leggibile
        then
        check=`stat --format=%G $i`

            if [[ $check = $group ]]
                then
                    echo "`pwd`/$i" >> "$OutFile"
                    echo "CONTENUTO DEL FILE $i:"
                    echo "`head -n $N $i`"
                    echo " "
                    echo " "

                else
                    echo "File non appartenente al gruppo $group"
            fi
    elif test -d "$i"  #file è una directory
        then
            "$0" "$group" "$N" "$OutFile" "$i"
    fi

done


