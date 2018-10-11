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

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

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
