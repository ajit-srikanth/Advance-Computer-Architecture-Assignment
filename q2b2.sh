#!/bin/bash

for k in {4..14}
do
    N=$((2**k))
    echo "Running with N=$N"
    g++ -O3 -DN=$N matmul_3d.cpp -o matmul_3d.out && sudo /usr/lib/linux-tools/5.4.0-149-generic/perf stat -e task-clock,cycles,instructions,cache-references,cache-misses -d ./matmul_3d.out
done

