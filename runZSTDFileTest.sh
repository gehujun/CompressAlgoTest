#!/bin/bash

set -e

DATA_FOLDER="/home/hustsss/dataset/silesia"
RESULT_FOLDER="/home/hustsss/dataset/result"

for file in $(ls $DATA_FOLDER)
do 
    if [ -d "$RESULT_FOLDER/$file.zstd1" ]; then 
        rm $RESULT_FOLDER/$file.zstd1
    fi
    zstd --fast=1 $DATA_FOLDER/$file -o $RESULT_FOLDER/$file.zstd1 >> ./zstd.log
done