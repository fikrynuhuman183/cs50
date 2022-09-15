// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



//storing size
int sizef = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1175;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //obtain the hash value for the word
    int hword = hash(word);

    //setup cursor
    node* cursor = malloc(sizeof(node));
    if(cursor == NULL)
    {
        return false;
    }
    cursor = table[hword];
    do
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }while(cursor->next != NULL);

    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int sum = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        if(isalpha(word[i]) != 0)
        {
            char tmp = tolower(word[i]);
            sum += tmp - 96;
        }
        else
        {
            continue;
        }
    }
    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary as file
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        return false;
    }
    //
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char wordict[LENGTH + 1];

    while(fscanf(dict, "%s", wordict) != EOF)
    {
        //obtain the hashvalue
        int hashword = hash(wordict);

        //allocate space for node
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }

        strcpy(n->word, wordict);
        n->next = NULL;

        if(table[hashword] == NULL)
        {
            table[hashword] = n;
        }
        else
        {
            n->next = table[hashword]->next;
            table[hashword]->next = n;
        }
        sizef++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(sizef == 0)
    {
        return 0;
    }
    else
    {
        return sizef;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = malloc(sizeof(node));
    node *tmp = malloc(sizeof(node));

    if(cursor == NULL || tmp == NULL)
    {
        return false;
    }

    for(int i = 0; i < N; i++)
    {
        cursor = tmp = table[i];

            if(cursor == NULL)
            {
                free(cursor);
            }
            else
            {
                do
                {
                    cursor = cursor->next;
                    free(tmp);
                    tmp = cursor;
                }while(cursor != NULL);
            }
    }
    free(tmp);
    return true;
}
