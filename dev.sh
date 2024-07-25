#!/bin/bash

gcc -o test.exe main.c src/hash_table.c src/prime.c -lm

if [ $? -eq 0 ]; then
    ./test.exe
else
    echo "Compilation failed."
fi
