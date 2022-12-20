#!/bin/bash
rm -r ./Build
mkdir ./Build
cmake -S ./ -B ./Build
# cp ./GUI ./Build -r
cp ./icons ./Build -r
cp ./levels ./Build -r
mkdir ./Build/bin
cd ./Build
make
mv ./Arcanoid_cpp ./bin/

rm ./.qt -r
rm ./CMakeFiles -r
rm ./cmake_install.cmake
rm ./CMakeCache.txt
rm ./Arcanoid_cpp_autogen -r
rm Makefile




