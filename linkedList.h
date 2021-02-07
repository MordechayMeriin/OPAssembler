#include "dataModel.h"

typedef struct lnode List;

struct lnode{
    struct lnode *next;
    Word value;
};

List *listalloc();

void addToList(struct lnode *list, Word *value);

Word getFromList(struct lnode *list, int index);

