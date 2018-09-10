/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)
        return false;

    /**
     * Linear searching algorithm for any integer arrays
     */
    // for (int i = 0; i < n; i++)
    //     if (values[i] == value)
    //         return true;
    // return false;

    /**
     * Binary searching algorithm only for sorted integer arrays
     */
    int minIndex = 0;
    int midIndex = 0;
    int maxIndex = n - 1;

    while (minIndex <= maxIndex) {
        midIndex = (minIndex + maxIndex) / 2;

        if (value < values[midIndex])
            maxIndex = midIndex - 1;
        else if (value > values[midIndex])
            minIndex = midIndex + 1;
        else
            return true;
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool nextRun = false;

    do {
        nextRun = false;
        for (int i = 0; i < n - 1; i++) {
            if (values[i] > values[i+1]) {
                values[i] ^= values[i+1] ^= values[i] ^= values[i+1];
                nextRun = true;
            }
        }
    } while(nextRun);

    return;
}