#!/bin/sh

mkdir build
clang -g -O0 test.c ../value.c ../backward.c ../topo.c -o build/test
build/test
