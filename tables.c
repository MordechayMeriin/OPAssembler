#include "tables.h"
#include <stdlib.h>
#include <string.h>

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

void addToTable(struct symbols *newS, char *name, char *attributes, int val)
{
    if(newS == NULL)
    {  
        newS= Slistalloc();
        strcpy(newS->name ,*name);
        strcpy(newS->attributes ,*attributes);
        newS->value=val;       
    }
    else if (strcmp(newS->name, *name)==0)
    {
        errorLog(0/*need to add line number!!!*/,"two symbols with the same name");
    }
    else if(newS->next == NULL)
    {  
        newS->next = Slistalloc();
        strcpy(newS->next->name ,*name);
        strcpy(newS->next->attributes ,*attributes);
        newS->next->value=val;       
    }
    else
    {
        addToTable(newS->next, name, attributes, val);
    }
        
}

void setVal(struct symbols *s, int val)
{
    if(strstr(s->attributes, "data"))
        s->value+=val;
    if(s->next != NULL)
        setVal(s->next, val);
}

void setAddress(struct symbols *s, char *name, Int12 address) /*for the second run*/
{
    if (strcmp(s->next->name, *name)==0)
    {
        s->address=address;
    }
    else if(s->next != NULL)
        setAddress(s->next, name, address);
    else
    {
        /*error*/
    }
}
