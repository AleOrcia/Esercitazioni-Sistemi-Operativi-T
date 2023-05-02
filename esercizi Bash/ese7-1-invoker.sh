#!/bin/bash

dir=$1
group=$2
text=$3

if [ $# -ne 3 ]
then echo ERRORE numero argomenti; exit
fi


if  [[ "$0" = /* ]] 
    then
        dir_name=`dirname "$0"`
        recursive_cmd="$dir_name/ese7-1-recurse.sh"

elif [[ "$0" = */* ]]
    then
        dir_name=`dirname "$0"`
        recursive_cmd="`pwd`/$dir_name/ese7-1-recurse.sh"

    else
        recursive_cmd=ese7-1-recurse.sh
        
fi

"$recursive_cmd" "$dir" "$group" "$text"