#!/bin/sh

mkdir build
rm build/test
clang -g -O0 test.c ../value.c ../backward.c ../topo.c ../ops.c -o build/test
build/test
