#include "dataModel.h"

#ifndef TABLES_INCLUDED
#define TABLES_INCLUDED

struct objects /*output table*/
{
    int address;
    int line: 12;
    char ARE;
};

struct label /*entries and externals tables*/
{
    char name[10];
    int address;
};

/*struct symbols
{
    char symbol[10];
    int value;
    char attributes[4]; /*code/entry/data/external*
};*/
typedef struct symbols{
    Int12 address;
    char *name;
    char *attributes;
    struct symbols *next;
    int value;
} Symbols;

Symbols *Slistalloc();

void addToTable(struct symbols *newS, char *name, char *attributes, int val);

void setVal(struct symbols *s, int val);

void setAddress(struct symbols *s, char *name, Int12 address); /*for the second run*/

#endif