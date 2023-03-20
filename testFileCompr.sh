#!/bin/bash

set -e

COMPRESSTYPE=$1
echo $COMPRESSTYPE

g++ -o testFile ./runTest.cpp -lzstd -g -llz4

DATA_FOLDER="/home/hustsss/dataset/silesia"
RESULT_FOLDER="/home/hustsss/dataset/result"

for file in $(ls $DATA_FOLDER)
do 
    ./testFile -f -i $DATA_FOLDER/$file -o ./result/$file.zstd1
done
