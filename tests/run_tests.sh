#!/bin/sh

echo "=== Basic tests ==="
mkdir -p build
rm -f build/test
clang -g -O0 test.c ../value.c ../backward.c ../topo.c ../ops.c -o build/test
./build/test

echo "=== Tensor tests ==="
clang -g -O0 test_tensors.c ../value.c ../backward.c ../topo.c ../ops.c -o build/test_tensors
build/test_tensors
