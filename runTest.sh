#!/bin/bash

set -e

COMPRESSTYPE=$1
echo $COMPRESSTYPE

g++ -o test ./runTest.cpp -lzstd -g -llz4

DATA_FOLDER="/home/hustsss/dataset/silesia"
RESULT_FOLDER="/home/hustsss/dataset/result"

for file in $(ls $DATA_FOLDER)
do 
    if [ $COMPRESSTYPE == "zstd:1" ]; then 
        ./test -c -t zstd:1 -i $DATA_FOLDER/$file -o $RESULT_FOLDER/$file 
    elif [ $COMPRESSTYPE == "zstd:9" ]; then 
        ./test -c -t zstd:9 -i $DATA_FOLDER/$file -o $RESULT_FOLDER/$file 
    elif [ $COMPRESSTYPE == "zstd:22" ]; then 
        ./test -c -t zstd:22 -i $DATA_FOLDER/$file -o $RESULT_FOLDER/$file 
    elif [ $COMPRESSTYPE == "lz4" ]; then 
        ./test -c -t lz4 -i $DATA_FOLDER/$file -o $RESULT_FOLDER/$file 
    fi
done
