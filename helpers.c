#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

const int SORT_INPUTS = 2;
const int SEARCH_INPUTS = 3;
const int ARR_BUFFER_SIZE = 100;

int is_valid_sort_input(char* name, int argc, char *argv[])
{
    if (argc != SORT_INPUTS)
    {
        printf("usage: ./%s <filepath>\n", name);
        return 1;
    }

    char *pathname = argv[1];
    FILE *file = fopen(pathname, "r");

    if (file == NULL)
    {
        printf("Wrong file path %s\n", pathname);
        return 1;
    }

    fclose(file);

    return 0;
}

int is_valid_search_input(char* name, int argc, char *argv[])
{
    if (argc != SEARCH_INPUTS)
    {
        printf("usage: ./%s <target> <filepath>\n", name);
        return 1;
    }

    int target;

    if (string_to_int(argv[1], &target) != 0)
        return 1;

    char *pathname = argv[2];
    FILE *file = fopen(pathname, "r");

    if (file == NULL)
    {
        printf("Wrong file path %s\n", pathname);
        return 1;
    }

    fclose(file);

    return 0;
}

int* read_numbers(FILE *file, int *n)
{
    int number;
    int arrBuffer = ARR_BUFFER_SIZE;
    int *arr = malloc(arrBuffer * sizeof(int));
    
    if (arr == NULL)
    {
        printf("Couldn't allocate memory for array\n");
        return NULL;
    }

    while (fscanf(file, "%i", &number) == 1)
    {
        (*n)++;

        if (*n >= arrBuffer)
        {
            arrBuffer *= 2;
            int *tmpArr = realloc(arr, arrBuffer * sizeof(int));

            if (tmpArr == NULL)
            {
                printf("Couldn't allocate memory for array\n");
                free(arr);
                return NULL;
            }

            arr = tmpArr;
        }

        arr[*n - 1] = number;
    }

    return arr;
}

void write_numbers(FILE *file, int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
            fprintf(file, "%i ", arr[i]);
        else
            fprintf(file, "%i", arr[i]);
    }
}

int string_to_int(char *s, int *n)
{
    char *remaining;
    long result;

    result = strtol(s, &remaining, 10);

    if (remaining == s)
    {
        printf("Second argument is not a number.\n");
        return 1;
    }

    if (*remaining != '\0')
    {
        printf("Invalid character: %c\n", *remaining);
        return 1;
    }
    
    if (result < INT_MIN || result > INT_MAX)
    {
        printf("number %ld exceeded integer limits.\n", result);
        return 1;
    }

    *n = (int) result;

    return 0;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}