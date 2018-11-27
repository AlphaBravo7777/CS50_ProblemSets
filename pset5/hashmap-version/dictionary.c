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

// datatype for dictionary list
typedef struct dictList {
    struct dictList *nextNode;
    char dictWord[];
} dictList;

dictList *hashMap[HASHMAP_SIZE] = {};
dictList *currNode = NULL;

FILE *dictFile = NULL;
unsigned dictSize = 0;
char wordBuf[LENGTH + 2];

/**
 * Simple quick hashing
 */
unsigned hash(const char *wordKey) {
    unsigned h = wordKey[0];
    for (int i = 1; wordKey[i]; h = h * 37 + wordKey[i], i++) {}
    return h % HASHMAP_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    for (int i = 0, wordLength = strlen(word); i <= wordLength; i++)
        wordBuf[i] = tolower(word[i]);

    for (currNode = hashMap[hash(wordBuf)]; currNode; currNode = currNode->nextNode)
        if (!strcmp(wordBuf, currNode->dictWord))
            return true;

    return false;
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

        currNode = malloc(sizeof(currNode) + strlen(wordBuf) + 1);
        if (!currNode) {
            printf("Memory allocation error.\n");
            unload();
            return false;
        }

        strcpy(currNode->dictWord, wordBuf);
        dictSize++;

        unsigned hashIndex = hash(wordBuf);
        currNode->nextNode = hashMap[hashIndex];
        hashMap[hashIndex] = currNode;
    }

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned size()
{
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    dictList *tempNode = NULL;

    for (int i = 0; i < HASHMAP_SIZE; i++) {
        currNode = hashMap[i];

        while (currNode) {
            tempNode = currNode;
            currNode = currNode->nextNode;
            free(tempNode);
        }
    }

    if (fclose(dictFile))
        return false;

    return true;
}
