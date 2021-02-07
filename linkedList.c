#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"
#include "common.h"

List *listalloc()
{
    List *p;
    p = (List *)calloc(sizeof(List), 1);
    if (p == NULL)
    {
        mallocError("Linked list node");
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

