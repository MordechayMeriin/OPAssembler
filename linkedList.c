#include <stdlib.h>
#include "dataModel.c"

typedef struct lnode List;

struct lnode{
    struct lnode *next;
    Word value;
};

List *listalloc()
{
    List *p;
    p = (List *)calloc(sizeof(List), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for the linked list.");
        exit(2);
    }  
    return p;
}

void addToList(struct lnode *list, Word *value)
{
    if(list->next == NULL)
    {
        List *newList;
        list->value = *value;       
        newList = listalloc();          
        list->next = newList;
    }
    else
    {
        addToList(list->next, value);
    }
        
}

Word getFromList(struct lnode *list, int index)
{
    struct lnode *pCurrentNode = list;
    int i;
    for (i = 0; i < index; i++)
    {
        if (pCurrentNode->next == NULL)
        {
            /* Handle error: Index out of the boundary of the array. */
            printf("%s\n", "");
        }
        
        pCurrentNode = pCurrentNode->next;
    }
    return pCurrentNode->value;
}

