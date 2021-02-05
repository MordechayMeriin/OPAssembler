#include "dataModel.c"
#include "common.c"
#define HASHSIZE 101
#define RULESNUM 16
#define LETTERSNUM 31


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
    
    if (strCompare(s, np->name))
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
        printf("malloc: failed in install to hash table.");
        exit(2);
    }
    hashval = hash(rule.name);
    hashTab[hashval] = np;    
    *np = rule;
    return np;
}

void createRulesTable()
{
    Rule rules[RULESNUM] = {
        {0,0,"mov",{1,1,0,1},{0,1,0,1}},
        {1,0,"cmp",{1,1,0,1},{1,1,0,1}},
        {2,10,"add",{1,1,0,1},{0,1,0,1}},
        {2,11,"sub",{1,1,0,1},{0,1,0,1}},
        {4,0,"lea",{0,1,0,0},{0,1,0,1}},
        {5,10,"clr",{0,0,0,0},{0,1,0,1}},
        {5,11,"not",{0,0,0,0},{0,1,0,1}},
        {5,12,"inc",{0,0,0,0},{0,1,0,1}},
        {5,13,"dec",{0,0,0,0},{0,1,0,1}},
        {9,10,"jmp",{0,0,0,0},{0,1,1,0}},
        {9,11,"bne",{0,0,0,0},{0,1,1,0}},
        {9,12,"jsr",{0,0,0,0},{0,1,1,0}},
        {12,0,"red",{0,0,0,0},{0,1,0,1}},
        {13,0,"prn",{0,0,0,0},{1,1,0,1}},
        {14,0,"rts",{0,0,0,0},{0,0,0,0}},
        {15,0,"stop",{0,0,0,0},{0,0,0,0}}
    };

    int i;
    for (i = 0; i < RULESNUM; i++)
    {
        setRule(rules[i]);
    }
}
