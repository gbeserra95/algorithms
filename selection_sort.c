#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

void selection_sort(int n, int *arr);

int main(int argc, char *argv[])
{
    if (is_valid_sort_input("selection_sort", argc, argv) != 0)
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

    selection_sort(n, arr);
    
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

void selection_sort(int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
            swap(&arr[i], &arr[minIndex]);
    }
}
