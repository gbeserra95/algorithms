#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void linear_search(int target, int n, int *arr);

int main(int argc, char *argv[])
{
    if (is_valid_search_input("linear_search", argc, argv) != 0)
        return 1;

    char *filepath = argv[2];
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
    {
        printf("Couldn't read file.\n");
        return 1;
    }

    int n = 0;
    int *arr = read_numbers(file, &n);

    if (arr == NULL)
        return 1;

    int target = atoi(argv[1]);

    linear_search(target, n, arr);

    fclose(file);
    free(arr);
    
    return 0;
}

void linear_search(int target, int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            printf("Found at index %i!\n", i);
            return;
        }
    }

    printf("Not found!\n");
}