#ifndef LINKED_LIST_INCLUDED
#define LINKED_LIST_INCLUDED

#include "dataModel.h"


typedef struct lnode{
    struct lnode *next;
    Row value;
}List;

List *listalloc();
void printlist(struct lnode *list);
void addToList(struct lnode *list, Row *value); /*add new row to list*/

Row getFromList(struct lnode *list, int index);

typedef struct att{
    unsigned int code: 1;
    unsigned int data: 1;
    unsigned int external: 1;
    unsigned int entry: 1;
}Attributes;

typedef struct symbols{
    Int12 value;
    char *name;
    char *attributes;
    Attributes attributeList;
    struct symbols *next;
} Symbols;



Symbols *Slistalloc();

void setData(List *Dlist); /*update the addresses of the data with IC*/

void addToTable(struct symbols *newS, char *name, char *attributes, int attribute, int val, int lineNumber, int allowDup);

void setVal(struct symbols *s, int val); /*update the values of the symbols*/

void printSymbols(struct symbols *S, int num);


#endif