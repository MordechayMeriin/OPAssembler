#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "common.h"
#include "errors.h"

List *listalloc()
{
    List *p;
    Row *R=ralloc();
    p = (List *)calloc(sizeof(List), 1);
    if (p == NULL)
    {
        mallocError("Linked list node");
    }  
    p->next = NULL;
    p->value=*R;
    return p;
}
void printlist(struct lnode *list)
{
    if(list->next != NULL)
    {
        printf("address=%d value=%d\n",list->value.address, list->value.value);
        printlist(list->next);
    }
}

void addToList(struct lnode *list, Row *value)
{
    if(list->next == NULL)
    {
        
        List *newList;
        list->value = *value;       
        newList = listalloc();          
        list->next = newList;
        newList->next = NULL;
    }
    else
    {
        addToList(list->next, value);
    }
}

Row getFromList(struct lnode *list, int index)
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

Symbols *Slistalloc()
{
    Symbols *p;
    p = (Symbols *)calloc(sizeof(Symbols), 1);
    if (p == NULL)
    {
        mallocError("Symbols list node");
    }
    else
    {
        char *tmp = (char *)calloc(sizeof(char), 1);
        p->name = tmp;
        tmp = (char *)calloc(sizeof(char), 1);
        p->attributes = tmp;
    }
    return p;
}

void addToTable(struct symbols *newS, char *name, char *attributes, int val, int lineNumber)
{
    if (strcmp(newS->name, name)==0)
    {
        if (strcmp(attributes, "external"))
        {
            errorLog(lineNumber, "two symbols with the same name");
        }
    }
    else if(newS->next == NULL)
    {
        newS->next = Slistalloc();
        strcpy(newS->name ,name);
        strcpy(newS->attributes ,attributes);
        newS->value.value=val;
    }
    else
    {
        addToTable(newS->next, name, attributes, val, lineNumber);
    }
        
}

void setVal(struct symbols *s, int val)
{
    if(strstr(s->attributes, "data"))
        s->value.value+=val;
    if(s->next != NULL)
        setVal(s->next, val);
}

void printSymbols(struct symbols *S, int num)
{
    if(S->next != NULL)
    {
    printf("symbol n%d: %s, %s, %d\n", num, S->name, S->attributes, S->value.value);
        printSymbols(S->next, num+1);
    }    
}

void setData(List *Dlist)
{
    extern int ICF;
    Dlist->value.address+=ICF;
    if(Dlist->next!=NULL)
        setData(Dlist->next);
}