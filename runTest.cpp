#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <assert.h>
#include <fstream>
#include <zstd.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <lz4.h>
#include <chrono>

#include "streaming_compression.hpp"
#include "lpaq1.hpp"

using namespace std;
#define BLOCKSIZE 1024 * 16

enum COMPTYPE{
    ZSTD,
    LZ4,
    LPAQ
};

// to compress: ./app -t COMPTYPE inputPath outputPath
// to decompress: ./app d inputPath

int main(int argc, char** argv){
    // char inputPath[100] = argv[2];
    assert(argc >= 2);
    MODE mode;
    const char *input_pathname = NULL, *output_pathname = NULL, *compress_algo = NULL;
    int opt;

    while((opt = getopt(argc, argv, "fcxi:t:o:b:")) != -1) {
        switch (opt) {
        case 'f':
            mode = FILECOMPRESS;
            break;
        case 'c':
            mode = COMPRESS;
            break;
        case 'x':
            mode = DECOMPRESS;
            break;  
        case 'i':
            input_pathname = optarg;
            break;
        case 'o':
            output_pathname = optarg;
            break;
        case 't':
            compress_algo = optarg;
            break;
        default:
            break;
        }
    }

    if(!input_pathname || !output_pathname){
        cout<<"please input the file path"<<endl;
        return 0;
    }

    fstream inFp;
    inFp.open(string(input_pathname), ios::in);
    fstream outFp;
    outFp.open(string(output_pathname), ios::out);

    int originSize = 0;
    inFp.seekg(0, ios::end);
    originSize = inFp.tellg();
    inFp.seekg(0, ios::beg);

    char buf[BLOCKSIZE];
    char out[BLOCKSIZE];
    int readSize = 0;
    int compSize = 0;
    double time = 0;
    if(mode == FILECOMPRESS) {
        int cLevel = 1;
        int nbThreads = 4;
        char* const outFilename = createOutFilename_orDie(input_pathname);
        compressFile_orDie(input_pathname, output_pathname, 1, 1);
    } else {
        while(readSize = inFp.read(buf,BLOCKSIZE).gcount()){    
            if(string(compress_algo) == "zstd:22"){
                auto start = chrono::high_resolution_clock::now();
                compSize += ZSTD_compress(out, BLOCKSIZE, buf, BLOCKSIZE, 22);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
            } else if(string(compress_algo) == "zstd:9"){ 
                auto start = chrono::high_resolution_clock::now();
                compSize += ZSTD_compress(out, BLOCKSIZE, buf, BLOCKSIZE, 9);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
            } else if(string(compress_algo) == "zstd:1"){
                auto start = chrono::high_resolution_clock::now();
                compSize += ZSTD_compress(out, BLOCKSIZE, buf, BLOCKSIZE, 1);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
            } else if(string(compress_algo) == "lz4"){
                auto start = chrono::high_resolution_clock::now();
                compSize += LZ4_compress_default(buf, out, BLOCKSIZE, BLOCKSIZE);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
            } else if(string(compress_algo) == "lpaq1"){
                auto start = chrono::high_resolution_clock::now();
                compSize += lpaq_compressBlock(buf, readSize, out, 0);
                auto end = chrono::high_resolution_clock::now();
                time += chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
            }
        }
    }
    
    cout<<"filePath:\t"<<string(input_pathname)<<endl;
    cout<<"origin size: \t"<<originSize;
    cout<<"\t after compress size is : \t"<<compSize<<endl;
    cout<<"compress time is: \t"<<time<<endl;

    return 0;
}