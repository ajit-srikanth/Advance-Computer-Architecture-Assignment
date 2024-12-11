#!/bin/bash

for k in {1..7}
do
    N=$((2**k))
    echo "Running with TILE_SIZE=$N"
    g++ -O3 -DTILE_SIZE=$N matmul_tiled.cpp -o matmul_tiled.out && sudo /usr/lib/linux-tools/5.4.0-149-generic/perf stat -e task-clock,cycles,instructions,cache-references,cache-misses -d ./matmul_tiled.out
done


