// Implements a dictionary's functionality

#include <stdbool.h>

// Implement for using strcasecmp
#include <strings.h>
// Implement for using printf,fscan and etc.
#include <stdio.h>
// Implement for using malloc, free.
#include <stdlib.h>
// Implement for using strcpy.
#include <string.h>
// Implement for using tolower.
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2600;

// Init words count in dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Call Hash function to get a hash value of word.
    int index = hash(word);
    
    // Use hash value to access to the head of the link list.
    node *cursor = table[index];
    
    // Traverse the link list to find word.
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        
        cursor = cursor -> next;       
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int value = 0;
    unsigned int len = strlen(word);
    
    for (int i = 0; i < len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    

    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file, and check if open is success.
    FILE *file = fopen(dictionary, "r");
    
    if (file == NULL)
    {
        return false;
    }
    
    char word[LENGTH + 1];
    
    // Loop through dictionary, and copy words to hash table.
    
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node, and check if success. 
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        
        // Copy word into node.
        strcpy(n->word, word);
        n -> next = NULL;
        
        // Call hash function to get a hash value as index.
        int index = hash(word);
        
        // Insert new node to node list.
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n -> next = table[index];
            table[index] = n;
        }

        // Count words. 
        word_count++;
    }
    
    // Close dictionary file.
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through all hash table buckets.
    for (int i = 0; i < N; i++)
    {
        // Define cursor to point to bucket[i].
        node *cursor = table[i];
        
        // If cursor is not NULL, free each node in the link list.
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    
    return true;
}
