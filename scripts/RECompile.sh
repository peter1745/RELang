#!/bin/bash

if [ $1 = "release" ]
then
./build/Release-linux-x86_64/RELang-Compiler/RELang-Compiler $2
fi

if [ $1 = "debug" ]
then
./build/Debug-linux-x86_64/RELang-Compiler/RELang-Compiler $2
fi
