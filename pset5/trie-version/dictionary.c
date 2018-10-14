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

FILE *dictFile = NULL;

dictTrie *rootNode = NULL;
dictTrie *currNode = NULL;
dictTrie *lastNode = NULL;

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

    for (int i = 0; word[i] != '\0'; i++) {
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

    while (lastNode) {
        if (lastNode->isWord)
            dictSize++;

        lastNode = lastNode->ptrIn[PREV];
    }

    lastNode = currNode;

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
