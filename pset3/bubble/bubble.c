#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./bubble n\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int values[n];

    srand48((long int) time(NULL));

    printf("Unsorted array:\n");
    for (int i = 0; i < n; i++) {
        values[i] = (int) (drand48() * LIMIT);
        printf("%i\n", values[i]);
    }

    bool nextRun = true;
    
    while (nextRun) {
        nextRun = false;
        
        for (int i = 0; i < n - 1; i++) {
            if (values[i] > values[i+1]) {
                values[i] ^= values[i+1] ^= values[i] ^= values[i+1];
                nextRun = true;
            }
        }
    }

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%i\n", values[i]);

    return 0;
}
