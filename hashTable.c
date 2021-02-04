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
    /*np->next = hashTab[hashval];  */
    hashTab[hashval] = np;    
    np->val = rule;
    return np;
}

void createRulesTable()
{
    Rule mov = {0,0,"mov",{1,1,0,1},{0,1,0,1}};
    Rule cmp = {1,0,"cmp",{1,1,0,1},{1,1,0,1}};

    install("mov", mov);
    install("cmp", cmp);

    struct hnode *gotmov = lookup("mov");
    struct hnode *gotcmp = lookup("cmp");

    printf("This is mov: opcode: %d, funct: %d, name: %s. inval: %d %d %d %d, outval: %d %d %d %d.", 
    gotmov->val.opcode, gotmov->val.funct, gotmov->val.name, 
    gotmov->val.inAd.m0, gotmov->val.inAd.m1, gotmov->val.inAd.m2, gotmov->val.inAd.m3, 
    gotmov->val.outAd.m0, gotmov->val.outAd.m1, gotmov->val.outAd.m2, gotmov->val.outAd.m3);

    printf("This is cmp: opcode: %d, funct: %d, name: %s. inval: %d %d %d %d, outval: %d %d %d %d.", 
    gotcmp->val.opcode, gotcmp->val.funct, gotcmp->val.name, 
    gotcmp->val.inAd.m0, gotcmp->val.inAd.m1, gotcmp->val.inAd.m2, gotcmp->val.inAd.m3, 
    gotcmp->val.outAd.m0, gotcmp->val.outAd.m1, gotcmp->val.outAd.m2, gotcmp->val.outAd.m3);
}
