#!/bin/bash
python gen.py "$1" "$2"
mpicxx -o merge_sort main.cpp
mpirun -n "$3" merge_sort