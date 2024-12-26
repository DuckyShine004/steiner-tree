#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: <source filename> <input/output filename>"
    exit 1
fi

FILENAME="$1.cpp"

make SRC=$FILENAME

if [ $? -eq 0 ]; then
    ./$(basename "$1") < data/inputs/"$2.in" > data/outputs/"$2.out"
    cat data/outputs/"$2.out"
else
    echo "Compilation failed."
fi

