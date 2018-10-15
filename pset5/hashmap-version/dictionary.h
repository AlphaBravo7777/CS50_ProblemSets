/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word + null-terminator
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 46

// data type for dictionary hash map
typedef struct dictList {
    char dictWord[LENGTH];
    struct dictList *nextNode;
} dictList;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size();

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload();

#endif // DICTIONARY_H
