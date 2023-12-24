#!/bin/bash

OS=uname

rm -rf build
rm -rf debug
rm -rf release
rm -rf xcode-build
rm -rf eclipse-project

mkdir debug
cd debug
cmake ../src -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make
cd ..

mkdir release
cd release
cmake ../src -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make
cd ..

mkdir xcode-project
cd xcode-project
cmake ../src -G Xcode
cd ..

