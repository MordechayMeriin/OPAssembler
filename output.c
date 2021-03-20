#include "output.h"

void printCodeListDebug(List *list)
{
    printf("inside printCodeListDebug\n");

    while (list->next != NULL)
    {
        printf("%04d\t%03X\t%c\n", list->value.address, intTo12BitInt(list->value.value), list->value.ARE);
        list = list->next;
    }   
}
