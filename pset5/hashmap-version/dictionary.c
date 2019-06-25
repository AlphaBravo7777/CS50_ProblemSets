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
typedef struct dictBucket {
    struct dictBucket *nextWord;
    char dictWord[];
} dictBucket;

dictBucket *dictHashMap[HASHMAP_SIZE] = {};
dictBucket *currNode = NULL;

FILE *dictFile = NULL;
unsigned dictSize = 0;
char wordBuf[LENGTH + 2];

/**
 * Simple quick hashing
 */
unsigned hash(const char *wordKey) {
    unsigned h = wordKey[0];
    for (unsigned i = 1; wordKey[i]; h = h * 37 + wordKey[i], i++) {}
    return h % HASHMAP_SIZE;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    dictFile = fopen(dictionary, "r");
    if (!dictFile)
        return false;

    for (const size_t nodePtrSize = sizeof(currNode); fgets(wordBuf, LENGTH + 2, dictFile); ) {
        size_t wordBufLen = strlen(wordBuf);
        currNode = malloc(nodePtrSize + wordBufLen);
        if (!currNode) {
            unload();
            return false;
        }

        wordBuf[wordBufLen - 1] = '\0';
        strcpy(currNode->dictWord, wordBuf);
        dictSize++;

        unsigned hashIndex = hash(wordBuf);
        currNode->nextWord = dictHashMap[hashIndex];
        dictHashMap[hashIndex] = currNode;
    }

    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    for (unsigned i = 0, wordLength = strlen(word); i <= wordLength; i++)
        wordBuf[i] = tolower(word[i]);

    for (currNode = dictHashMap[hash(wordBuf)]; currNode; currNode = currNode->nextWord)
        if (!strcmp(wordBuf, currNode->dictWord))
            return true;

    return false;
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
    dictBucket *tempNode = NULL;

    for (unsigned i = 0; i < HASHMAP_SIZE; i++) {
        currNode = dictHashMap[i];

        while (currNode) {
            tempNode = currNode;
            currNode = currNode->nextWord;
            free(tempNode);
        }
    }

    if (fclose(dictFile))
        return false;

    return true;
}
