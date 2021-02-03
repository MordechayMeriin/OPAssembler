#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataModel.c"
#define HASHSIZE 101

struct hnode{
    struct hnode *next;
    char *name;
    Rule val;
};

char *strdup(const char *);

static struct hnode *hashTab[HASHSIZE];

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}
struct hnode *lookup(char *s)
{
    struct hnode *np;

    for (np = hashTab[hash(s)]; np != NULL; np=np->next)
    {
        if (strcmp(s, np->name))
        {
            return np;
        }       
    }
    return NULL;   
}

struct hnode *install(char *name, Rule rule)
{
    struct hnode *np;
    unsigned int hashval;

    np = malloc(sizeof(struct hnode));
    if (np == NULL || (np->name = strdup(name)) == NULL)
    {
        printf("malloc: failed in install to hash table.");
        exit(2);
    }
    hashval = hash(name);
    np->next = hashTab[hashval];       
    
    return np;
}
