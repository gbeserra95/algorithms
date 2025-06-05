#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void binary_search(int target, int startIndex, int endIndex, int *arr);

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

    binary_search(target, 0, n - 1, arr);

    fclose(file);
    free(arr);

    return 0;
}

void binary_search(int target, int startIndex, int endIndex, int *arr)
{
    if (endIndex < startIndex)
    {
        printf("Not found!\n");
        return;
    }

    int middleIndex = (endIndex + startIndex) / 2;

    if (arr[middleIndex] < target)
    {
        startIndex = middleIndex + 1;
        binary_search(target, startIndex, endIndex, arr);
    }
    else if (arr[middleIndex] > target)
    {
        endIndex = middleIndex - 1;
        binary_search(target, startIndex, endIndex, arr);
    }
    else
    {
        printf("Found at index %i!\n", middleIndex);
        return;
    }
}