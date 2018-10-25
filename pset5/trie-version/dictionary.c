/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

/**
* The size of the English alphabet, including apostrophe.
* The last index stores link to the previously created node.
* This will free up memory and calculate size of the dictionary for linear time.
* (pun: "PREVious" address of node and "PREView" for alphabet :-)
*/
#define PREV 27

// data type for dictionary tree
typedef struct dictTrie {
    bool isWord;
    struct dictTrie *ptrIn[PREV + 1];
} dictTrie;

dictTrie *rootNode = NULL;
dictTrie *currNode = NULL;
dictTrie *lastNode = NULL;

FILE *dictFile = NULL;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    dictFile = fopen(dictionary, "r");
    if (!dictFile)
        return false;

    rootNode = calloc(1, sizeof(*rootNode));
    if (!rootNode) {
        printf("Memory allocation error.\n");
        unload();
        return false;
    }

    currNode = rootNode;
    lastNode = rootNode;

    for (int a = fgetc(dictFile); a != EOF; a = fgetc(dictFile)) {
        if (a == '\n') {
            currNode->isWord = true;
            currNode = rootNode;
        }
        else {
            if (a == '\'')
                a = 'z' + 1;

            if (!currNode->ptrIn[a - 'a']) {
                currNode->ptrIn[a - 'a'] = calloc(1, sizeof(*currNode->ptrIn[a - 'a']));
                if (!currNode->ptrIn[a - 'a']) {
                    printf("Memory allocation error.\n");
                    unload();
                    return false;
                }

                currNode->ptrIn[a - 'a']->ptrIn[PREV] = lastNode;
                lastNode = currNode->ptrIn[a - 'a'];
            }

            currNode = currNode->ptrIn[a - 'a'];
        }
    }

    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    currNode = rootNode;

    for (int i = 0; word[i]; i++) {
        char a = tolower(word[i]);

        if (a == '\'')
            a = 'z' + 1;

        if (!currNode->ptrIn[a - 'a'])
            return false;

        currNode = currNode->ptrIn[a - 'a'];
    }

    return currNode->isWord;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size()
{
    unsigned int dictSize = 0;

    currNode = lastNode;

    while (currNode) {
        if (currNode->isWord)
            dictSize++;

        currNode = currNode->ptrIn[PREV];
    }

    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    while (lastNode) {
        currNode = lastNode;
        lastNode = lastNode->ptrIn[PREV];
        free(currNode);
    }

    if (fclose(dictFile))
        return false;

    return true;
}
