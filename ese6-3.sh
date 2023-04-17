#!/bin/bash

if [ $# != 3 ]
then echo Sintassi!; exit;
else echo OK
fi

M=$1
stringa=$2
filedirectory=$3

for i in `cat $filedirectory`
do
cd $i

for j in `ls`
do
if [[ -d $j ]]
then continue;
fi

occorrenze=`grep -o $stringa $j | wc -l`

if [ $occorrenze -gt $M ]
then
    dim=`ls -sh $j | awk '{print $1}'`
    echo "Il file $j nella directory $i contiene $dim di caratteri"
else
    echo "Non abbastanza occorrenze"
fi

done

done


