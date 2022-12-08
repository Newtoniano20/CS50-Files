// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

int size_dict = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    bool result = false;
    node *list = table[hash(word)];
    while (!(list == NULL))
    {
        if (strcasecmp(list->word, word) == 0)
        {
            result = true;
        }
        list = list->next;
    }
    return result;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    char first_letter = toupper(word[0]);
    char second_letter = toupper(word[1]);
    if (second_letter == 0)
    {
        second_letter = first_letter;
    }
    unsigned int result = 26 * (first_letter - 'A') + (second_letter - 'A');
    return result;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return 1;
        }
        new->next = NULL;
        strcpy(new->word, "");
        table[i] = new;
    }
    char *BUFFER = malloc(sizeof(char) * (LENGTH + 1));
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    while (fscanf(f, "%s", BUFFER) != EOF)
    {
        size_dict++;
        node *last = table[hash(BUFFER)];
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }
        new->next = NULL;
        strcpy(new->word, BUFFER);
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new;
        //printf("%s\n", last->word);
    }
    free(BUFFER);
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *last = table[i];
        while (!(last == NULL))
        {
            node *old = last;
            last = last->next;
            free(old);
        }
    }
    return true;
}
