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

// prime for max hash value
#define HASHMAP_SIZE 199999

FILE *dictFile = NULL;
unsigned int dictSize = 0;
char hashMap[HASHMAP_SIZE][LENGTH + 1] = {};
char wordBuf[LENGTH + 2];

/*
* Simple quick hashing with quadratic probing for resolving collisions
*/
unsigned int hashIndex(const char *wordKey, int i) {
    unsigned int h = 0;

    for (int j = 0, keyLength = strlen(wordKey); j < keyLength; j++)
        h = ((h << 8) ^ wordKey[j]) % (HASHMAP_SIZE - 1);

    return (h + i*i) % HASHMAP_SIZE;
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
        wordBuf[strlen(wordBuf) - 1] = '\0';

        int i = 0;
        for (; hashMap[hashIndex(wordBuf, i)][0]; i++) {}

        strcpy(hashMap[hashIndex(wordBuf, i)], wordBuf);
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

    for (int i = 0; hashMap[hashIndex(wordBuf, i)][0]; i++)
        if (!strcmp(wordBuf, hashMap[hashIndex(wordBuf, i)]))
            return true;

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
    if (fclose(dictFile))
        return false;

    return true;
}
