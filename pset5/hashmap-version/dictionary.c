/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define N 3

// max value of hash-function
#define HASHMAP_SIZE N*65536

FILE *dictFile = NULL;

dictList hashMap[HASHMAP_SIZE] = {};
dictList *currNode = NULL;

char wordBuf[LENGTH + 2];
unsigned int dictSize = 0;

unsigned int max_collisions = 0;

/**
 * Pearson hashing
 * (taken from https://en.wikipedia.org/wiki/Pearson_hashing)
 */
unsigned int hash(const char *word)
{
    static const unsigned char T[256] = {
        // 0-255 shuffled in any (random) order suffices
         98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219, //  1
         61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, //  2
         90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10, //  3
        237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, //  4
        123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, //  5
         59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, //  6
        197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, //  7
         39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99, //  8
        154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, //  9
        133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, // 10
        189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
        183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
        221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
          3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
        238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
         43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  // 16
    };

    unsigned char h0 = T[(word[0]) % 256];
    unsigned char h1 = T[(word[0] + 1) % 256];
    unsigned char h2 = T[(word[0] + 2) % 256];

    for (int i = 1, wordLength = strlen(word); i < wordLength; i++) {
        h0 = T[h0 ^ word[i]];
        h1 = T[h1 ^ word[i]];
        h2 = T[h2 ^ word[i]];
    }

    return ((h2%N) << 16) + (h1 << 8) + h0;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    dictFile = fopen(dictionary, "r");
    if (!dictFile)
        return false;

    while (fgets(wordBuf, LENGTH + 2, dictFile)) {
        unsigned int collisions = 0;
        wordBuf[strlen(wordBuf) - 1] = '\0';
        currNode = hashMap + hash(wordBuf);

        while (currNode->nextNode) {
            currNode = currNode->nextNode;
            collisions++;
        }

        if (collisions > max_collisions)
            max_collisions = collisions;

        currNode->nextNode = calloc(1, sizeof(*currNode->nextNode));
        if (!currNode->nextNode) {
            printf("Memory allocation error.\n");
            unload();
            return false;
        }

        strcpy(currNode->nextNode->dictWord, wordBuf);
        dictSize++;
    }

    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    for (int i = 0, wordLength = strlen(word); i <= wordLength; i++)
        wordBuf[i] = tolower(word[i]);

    currNode = hashMap[hash(wordBuf)].nextNode;

    while (currNode) {
        if (!strcmp(wordBuf, currNode->dictWord))
            return true;

        currNode = currNode->nextNode;
    }

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size()
{
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    dictList *tempNode = NULL;
    unsigned int busy_cells = 0;

    for (int i = 0; i < HASHMAP_SIZE; i++) {
        currNode = hashMap[i].nextNode;

        if (currNode)
            busy_cells++;

        while (currNode) {
            tempNode = currNode;
            currNode = currNode->nextNode;
            free(tempNode);
        }
    }

    printf("\nHASHMAP SIZE:\t%i\n", HASHMAP_SIZE);
    printf("BUSY CELLS:\t%i\n", busy_cells);
    printf("LOAD FACTOR:\tideal %.2f\treal %.2f\n", (double) dictSize / (N*65536), (double) busy_cells / (N*65536));
    printf("ALPHA FACTOR:\t%.2f\n", (double) dictSize / busy_cells);
    printf("MAX COLLISIONS:\t%i\n", max_collisions);

    if (fclose(dictFile))
        return false;

    return true;
}
