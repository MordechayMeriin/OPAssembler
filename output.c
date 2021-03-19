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