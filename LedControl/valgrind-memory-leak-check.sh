#!/bin/bash
valgrind --show-top-n=100 --tool=exp-dhat bin/Debug/LedControl > valgrind-out.txt 2>&1 && grep "none" -B4 -A10 valgrind-out.txt