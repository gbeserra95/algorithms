#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int ARGS_COUNT = 3;
const int RANDOM = -1;
const int RANGED = 0;

int validate_input(int argc, char *argv[]);
int generate_random_file(char *count);
int generate_ordered_file(char *start, char *end);
void usage();
int is_int(char *remaining, long n);

int main(int argc, char *argv[])
{
    int algorithmType;

    int input = validate_input(argc, argv);

    if(input == RANDOM)
        return generate_random_file(argv[2]);
    else if (input == RANGED)
        return generate_ordered_file(argv[1], argv[2]);

    return input;
}

int validate_input(int argc, char *argv[])
{
    if (argc != ARGS_COUNT)
    {
        usage();
        return 1;
    }
    
    if (strcmp(argv[1], "--random") == 0)
        return RANDOM;

    return RANGED;
}

int generate_ordered_file(char *start, char *end)
{
    char *startRemaining;
    char *endRemaining;

    long a;
    long b;

    a = strtol(start, &startRemaining, 10);

    if (is_int(startRemaining, a) != 0)
        return 1;

    b = strtol(end, &endRemaining, 10);

    if (is_int(endRemaining, b) != 0)
        return 1;

    FILE *file = fopen("numbers.txt", "w");

    if (file == NULL)
    {
        printf("Error to create file.\n");
        return 1;
    }

    if (a < b)
    {
        for (int i = a; i <= b; i++)
        {
            if (i < b)
                fprintf(file, "%i ", i);
            else
                fprintf(file, "%i\n", i);
        }
    }
    else if (a > b)
    {
        for (int i = a; i >= b; i--)
        {
            if (i > b)
                fprintf(file, "%i ", i);
            else
                fprintf(file, "%i\n", i);
        }
    }
    else
    {
        printf("<start> and <end> must be different.\n");
        usage();
        fclose(file);
        return 1;
    }
    
    fclose(file);
    return 0;
}

int generate_random_file(char *count)
{
    srand(time(NULL));

    char *remaining;
    long n;

    n = strtol(count, &remaining, 10);

    if (is_int(remaining, n) != 0)
        return 1;

    if (n <= 0)
    {
        printf("<count> must be greater than 0.\n");
        return 1;
    }

    FILE *file = fopen("numbers.txt", "w");

    if (file == NULL)
    {
        printf("Error to create file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
            fprintf(file, "%i ", (int) (rand() % n));
        else
            fprintf(file, "%i\n", (int) (rand() % n));
    }
    
    fclose(file);
    return 0;
}

void usage()
{
    printf("Usage:\n");
    printf("  ./generate_numbers <start> <end>           Generate numbers in order from <start> to <end>\n");
    printf("  ./generate_numbers --random <count>        Generate <count> random numbers\n");
    printf("\nExamples:\n");
    printf("  ./generate_numbers 1 5                     # Output: 1 2 3 4 5\n");
    printf("  ./generate_numbers 5 1                     # Output: 5 4 3 2 1\n");
    printf("  ./generate_numbers --random 5              # Output: 37 12 84 3 51\n");
}

int is_int(char *input, long n)
{
    if (*input != '\0')
    {
        printf("'%s' is not a valid integer.\n", input);
        printf("\n");
        usage();
        return 1;
    }

    if (n > INT_MAX || n < INT_MIN)
    {
        printf("%li must be an integer.\n", n);
        printf("\n");
        usage();
        return 1;
    }

    return 0;
}