#include "output.h"

void printCodeListDebug(List *list)
{
    int i;
    printf("inside printCodeListDebug\n");

    for (i = 0; i < 10; i++)
    {
        Row r = getFromList(list, i);
        printf("list item %d: %d\t%d\t%c\n", i, r.address, r.value, r.ARE);
    }

    

/*
    while (list->next != NULL)
    {
        printf("printCodeListDebug: list = %d\n", list->next->value.value);
        printf("printCodeListDebug: list->value.value = %d\n", list->value.address);
        printf("%d\t%d\t%c\n", list->value.address, list->value.value, list->value.ARE);
        list = list->next;
    }
    */
}