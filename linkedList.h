#include "dataModel.h"

typedef struct lnode List;

struct lnode{
    struct lnode *next;
    Word value;
};

List *listalloc();

void addToList(struct lnode *list, Word *value);

Word getFromList(struct lnode *list, int index);

typedef struct symbols{
    Int12 address;
    char *name;
    char *attributes;
    struct symbols *next;
    int value;
} Symbols;

Symbols *Slistalloc();

void addToTable(struct symbols *newS, char *name, char *attributes, int val, int lineNumber);

void setVal(struct symbols *s, int val);

void setAddress(struct symbols *s, char *name, Int12 address); /*for the second run*/