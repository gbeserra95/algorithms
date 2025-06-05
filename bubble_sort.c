#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

void bubble_sort(int n, int *arr);

int main(int argc, char *argv[])
{
    if (is_valid_sort_input("bubble_sort", argc, argv) != 0)
        return 1;

    char *filepath = argv[1];
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
    {
        printf("Couldn't read file.");
        return 1;
    }

    int n = 0;
    
    int *arr = read_numbers(file, &n);

    if (arr == NULL)
        return 1;

    bubble_sort(n, arr);

    fclose(file);

    file = fopen(filepath, "w");

    if (file == NULL)
    {
        printf("Couldn't read file.");
        return 1;
    }

    write_numbers(file, n, arr);

    fclose(file);
    free(arr);
    
    return 0;
}

void bubble_sort(int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        int swaps = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swaps++;
            }
        }

        if (swaps == 0)
            return;
    }
}