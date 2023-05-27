# CompressAlgoTest
This repos is used to test various compression algorithms

# lz4 and zstd should be installed in advance
#run zstd block test :x (x means compress level,1 9 22)
./runTest.sh zstd:1 
#run zstd file test 
./testFileCompr.sh 
#run lz4 test 
./runTest.sh lz4
#run lpaq1 test
./runTest.sh lpaq1
