#include <stdlib.h>
#include <string.h>
#include "rulesHash.h"
#include "common.h"

static Rule *hashTab[HASHSIZE];

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + LETTERSNUM * hashval;
    }
    return hashval % HASHSIZE;
}
Rule *getRule(char *s)
{
    Rule *np;

    if (hashTab[hash(s)] == NULL)
    {
        return NULL;
    }

    np = hashTab[hash(s)];
    
    if (strcmp(s, np->name) == 0)
    {
        return np;
    }       

    return NULL;   
}

Rule *setRule(Rule rule)
{
    Rule *np;
    unsigned int hashval;

    np = malloc(sizeof(Rule));
    if (np == NULL)
    {
        mallocError("Rules hash table");
    }
    hashval = hash(rule.name);
    hashTab[hashval] = np;    
    *np = rule;
    return np;
}

void createRulesTable()
{
    Rule rules[RULESNUM] = {
        {0,0,"mov",2,{1,1,0,1},{0,1,0,1}},
        {1,0,"cmp",2,{1,1,0,1},{1,1,0,1}},
        {2,10,"add",2,{1,1,0,1},{0,1,0,1}},
        {2,11,"sub",2,{1,1,0,1},{0,1,0,1}},
        {4,0,"lea",2,{0,1,0,0},{0,1,0,1}},
        {5,10,"clr",1,{0,0,0,0},{0,1,0,1}},
        {5,11,"not",1,{0,0,0,0},{0,1,0,1}},
        {5,12,"inc",1,{0,0,0,0},{0,1,0,1}},
        {5,13,"dec",1,{0,0,0,0},{0,1,0,1}},
        {9,10,"jmp",1,{0,0,0,0},{0,1,1,0}},
        {9,11,"bne",1,{0,0,0,0},{0,1,1,0}},
        {9,12,"jsr",1,{0,0,0,0},{0,1,1,0}},
        {12,0,"red",1,{0,0,0,0},{0,1,0,1}},
        {13,0,"prn",1,{0,0,0,0},{1,1,0,1}},
        {14,0,"rts",0,{0,0,0,0},{0,0,0,0}},
        {15,0,"stop",0,{0,0,0,0},{0,0,0,0}}
    };

    int i;
    for (i = 0; i < RULESNUM; i++)
    {
        setRule(rules[i]);
    }
}

void freeRulesTable()
{
    int i;
    for (i = 0; i < HASHSIZE; i++)
    {
        if (hashTab[i] != NULL)
        {
            free(hashTab[i]);
        }
    }
    
}

int isValidCommand(char *command)
{
    if (getRule(command) != NULL)
    {
        return 1;
    }
    return 0;
    
}

AddressingMethod *getAddressingMethod(Rule *rule, int operandType)
{
    if (operandType == SOURCE_OPERAND)
    {
        return &(rule->inAd);
    }
    return &(rule->outAd);
}