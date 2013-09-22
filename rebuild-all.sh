#!/bin/bash

rm -rf build
rm -rf xcode-build

mkdir build
cd build
cmake .. -G "Unix Makefiles"
make

cd ..

mkdir xcode-build
cd xcode-build
cmake .. -G Xcode

cd ..
