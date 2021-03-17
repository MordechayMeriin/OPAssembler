#include "output.h"

void printCodeListDebug(List *list)
{
    int i;
    printf("inside printCodeListDebug\n");

    for (i = 0; i < 10; i++)
    {
        Row r = getFromList(list, i);
        printf("list item %d: %d\t%x\t%c\n", i, r.address, r.value, r.ARE);
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
/*int hex12(int a)
{
    int i, tmp=0;
    for(i=0; i<12 ; i++)
    {
        tmp=tmp|(a&1);
        tmp=1<<tmp;
        a=1<<a;
    }
    return tmp;
}*/
void printDynamicListDebug(Array *arr)
{
    int i;
    for (i = 0; i < arr->used; i++)
    {
        printf("Row %d:\t%d\t%d\t%c\n",i , arr->array[i].address, arr->array[i].value, arr->array[i].ARE);
    }
    
}