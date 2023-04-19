#!/bin/bash

if [ $# -lt 2 ]
    then echo SINTASSIII; exit
fi

username=$1
shift
X=0

for dir in $*
do

    if [[ -d $dir ]]
        then echo OK
        else echo "Directory non esistente!"; exit
    fi

    test=`ls -l $dir | awk '{print $3}'`

    for i in $test
    do
        if [[ $i = $username ]]
            then echo "$dir"
            X=`expr $X + 1`
    
        fi 
    done

done

echo $X
