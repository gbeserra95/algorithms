#!/bin/bash

gcc generate_numbers.c helpers.c -o generate_numbers
gcc bubble_sort.c helpers.c -o bubble_sort
gcc selection_sort.c helpers.c -o selection_sort
gcc merge_sort.c helpers.c -o merge_sort
gcc linear_search.c helpers.c -o linear_search
gcc binary_search.c helpers.c -o binary_search

echo "Compilação concluída."
