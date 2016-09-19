#!/bin/bash
python gen.py "$1"
mpicxx -o merge_sort main.cpp
mpirun -n "$2" merge_sort