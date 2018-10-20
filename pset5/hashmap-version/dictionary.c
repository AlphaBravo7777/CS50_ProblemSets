#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// prime for max hash value
#define HASHMAP_SIZE 199999

FILE *dictFile = NULL;
unsigned int dictSize = 0;
bool busyList[HASHMAP_SIZE] = {};
char hashMap[HASHMAP_SIZE][LENGTH + 1] = {};
char wordBuf[LENGTH + 2];

/*
* Simple quick hashing with quadratic probing in load() and check() for resolving collisions
*/
int hash(const char *wordKey) {
    unsigned int h = wordKey[0];

    for (int j = 1, keyLength = strlen(wordKey); j < keyLength; j++)
        h = ((h << 8) ^ wordKey[j]) % (HASHMAP_SIZE - 1);

    return h;
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
        int hashIndex = hash(wordBuf);

        for (int i = 1; busyList[hashIndex]; i += 2, depth++)
            hashIndex = (hashIndex + i) % HASHMAP_SIZE;

        strcpy(hashMap[hashIndex], wordBuf);
        busyList[hashIndex] = true;
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

    for (int i = 1, hashIndex = hash(wordBuf); busyList[hashIndex]; i += 2) {
        if (!strcmp(wordBuf, hashMap[hashIndex]))
            return true;

        hashIndex = (hashIndex + i) % HASHMAP_SIZE;
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
    if (fclose(dictFile))
        return false;

    return true;
}
