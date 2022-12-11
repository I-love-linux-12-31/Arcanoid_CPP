#!/bin/bash
rm -r ./Build
mkdir ./Build
cmake -S ./ -B ./Build
# cp ./GUI ./Build -r
cp ./icons ./Build -r
cp ./levels ./Build -r
cd ./Build
make
rm ./.qt -r
rm ./CMakeFiles -r
rm ./cmake_install.cmake
rm ./CMakeCache.txt
rm ./Makefile


