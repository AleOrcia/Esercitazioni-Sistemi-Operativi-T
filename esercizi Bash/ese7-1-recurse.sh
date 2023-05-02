#!/bin/bash

dir=$1
group=$2
text=$3

if ! test -d "$dir"
    then

        if [[ -r "$dir" ]]
        then
            for check in `stat --format=%G $dir`
            do
                if [[ $check = $group ]]
                then
                    echo "`pwd`/$dir"
                    occorrenze=`grep -o $text $dir | wc -l`
                    echo "Il numero di occorrenze della stringa $string è $occorrenze"
                    echo " " #newline

                else
                    echo "File `pwd`/$dir non appartenente al gruppo $group"
                fi
            done
            
        fi

        
    else
        cd "$dir"
        for f in `ls` ; do
            "$0" "$f" "$group" "$text"
        done
fi