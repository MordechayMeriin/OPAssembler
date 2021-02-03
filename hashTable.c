#include <stdlib.h>
#include <string.h>
#include "dataModel.c"
#define HASHSIZE 101

struct hnode{
    struct hnode *next;
    char *name;
    Word val;
};

static struct hnode *hashTab[HASHSIZE];

