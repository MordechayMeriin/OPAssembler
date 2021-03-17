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
    p->next = NULL;
    return p;
}

void addToList(struct lnode *list, Row *value)
{
    printf("addToList: list.value.address = %d, value = %d\n", list->value.address, value->address);
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
    printf("getFromList: list.value.address = %d, index = %d\n", list->value.address, index);
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
    return p;
}

void addToTable(struct symbols *newS, char *name, char *attributes, int val, int lineNumber)
{
    printf("inside addToLabel. name = %s, attributes = %s, val = %d, lineNumber = %d.\n", name, attributes, val, lineNumber);
    printf("inside addToLabel. newS add = %d.\n", newS);
    printf("inside addToLabel. newS: name = %s, attributes = %s, value = %d, next = %d.\n", newS->name, newS->attributes, newS->value.value, newS->next);
    if(newS == NULL)
    {  
        printf("addToLabel: newS == NULL\n");
        newS= Slistalloc();
        strcpy(newS->name ,name);
        strcpy(newS->attributes ,attributes);
        newS->value.value=val;       
    }
    else if (strcmp(newS->name, name)==0)/*the newS is not null at the first time, but everything inside is null, so we gwt a sepmentation faulte here*/
    {
        printf("addToLabel: after name compare\n");
        if (strcmp(attributes, "external"))
        {
            errorLog(lineNumber, "two symbols with the same name");
        }
    }
    else if(newS->next == NULL)
    {  
        newS->next = Slistalloc();
        strcpy(newS->next->name ,name);
        strcpy(newS->next->attributes ,attributes);
        newS->next->value.value=val;       
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