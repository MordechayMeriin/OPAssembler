#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "common.h"
#include "errors.h"

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

void addToList(struct lnode *list, Row *value)
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
    printf("symbol n%d: %s, %s, %d\n", num, S->name, S->attributes, S->value.value);
    if(S->next != NULL)
    {
        printSymbols(S->next, num+1);
    }    
}

/*void setAddress(struct symbols *s, char *name, Int12 address)
{
    if (strcmp(s->next->name, name)==0)
    {
        s->address=address;
    }
    else if(s->next != NULL)
        setAddress(s->next, name, address);
    else
    {
        error
    }
}*/