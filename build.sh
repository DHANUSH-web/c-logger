#!/bin/bash

mkdir -p out
cd out
cmake ..
cmake --build .
echo -e "\n"
./ModularC
