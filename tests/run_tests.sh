#!/bin/sh

mkdir build
clang -g -O0 tests/centigrad_tests.c value.c backward.c topo.c -o build/test
build/test
