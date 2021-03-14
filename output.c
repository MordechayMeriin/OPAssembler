#include "output.h"

void printCodeListDebug(List *list)
{
    while (list->next != NULL)
    {
        printf("%d\t%d\t%c", list->value.address, list->value.value, list->value.ARE);
    }
    
}