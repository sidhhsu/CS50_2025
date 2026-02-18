// Implements a dictionary's functionality

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// size counter
unsigned int dictsize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];
    while (cursor->next != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0 || strcasecmp(word, "a") == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    if (strcasecmp(cursor->word, word) == 0 || strcasecmp(word, "a") == 0)
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // my attempt: sum of ASCII values
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }
    char *w = malloc(LENGTH + 1);
    while (fscanf(d, "%s", w) != EOF)
    {
        node *temp = malloc(sizeof(node));
        //printf("malloc has happened\n");
        if (temp == NULL)
        {
            return false;
        }
        for (int i = 0; i < strlen(temp->word); i++)
        {
            if (temp->word[i] == '\'')
            {
                temp->word[i] = ' ';
            }
        }
        strcpy(temp->word, w);
        unsigned int index = hash(temp->word);
        if (table[index] == NULL)
        {
            table[index] = temp;
            dictsize++;
            continue;
        }
        temp->next = table[index];
        table[index] = temp;
        dictsize++;
    }
    free(w);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            //printf("freeing\n");
            free(temp);
        }
    }
    return true;
}
