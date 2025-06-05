#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

void merge_sort(int n, int *arr);

int main(int argc, char *argv[])
{
    if (is_valid_sort_input("merge_sort", argc, argv) != 0)
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

    merge_sort(n, arr);
    
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

void merge_sort(int n, int *arr)
{
    if (n <= 1)
        return;

    int n1 = n / 2;
    int n2 = n - n1;

    int *left_arr = malloc(n1 * sizeof(int));
    int *right_arr = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[i];

    for (int j = n1; j < n; j++)
        right_arr[j - n1] = arr[j];

    merge_sort(n1, left_arr);
    merge_sort(n2, right_arr);

    int i = 0;
    int j = 0;
    int count = 0;

    while (i < n1 && j < n2)
    {
        if (left_arr[i] < right_arr[j])
        {
            arr[count] = left_arr[i];
            i++;
            count++;
        }
        else
        {
            arr[count] = right_arr[j];
            j++;
            count++;
        }
    }

    while (i < n1)
    {
        arr[count] = left_arr[i];
        i++;
        count++;
    }

    while (j < n2)
    {
        arr[count] = right_arr[j];
        j++;
        count++;
    }

    free(left_arr);
    free(right_arr);
}