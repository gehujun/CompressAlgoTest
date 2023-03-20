#!/bin/bash

set -e

g++ -o test ./runTest.cpp -lzstd -g -llz4

./test -c -t lpaq1 -i  ~/dataset/silesia/x-ray -o ./result/silesia.lpaq

