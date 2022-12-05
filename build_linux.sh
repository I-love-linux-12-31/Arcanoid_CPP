#!/bin/bash
rm -r ./Build
mkdir ./Build
cmake -S ./ -B ./Build
# cp ./GUI ./Build -r
cp ./icons ./Build -r
cp ./levels ./Build -r
cd ./Build
make