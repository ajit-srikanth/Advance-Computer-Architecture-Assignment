#!/bin/bash

for k in {1..7}
do
    N=$((2**k))
    echo "Running with TILE_SIZE=$N and N = 512"
    g++ -O3 -DTILE_SIZE=$N -DN=512 matmul_tiled.cpp -o matmul_tiled_$N.out && sudo valgrind --tool=cachegrind --I1=32768,32,64 --L2=1048576,16,64 ./matmul_tiled_$N.out
done


