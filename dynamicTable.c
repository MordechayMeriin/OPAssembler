#include "dynamicTable.h"

#define INITIAL_SIZE 10

Array *createDynamicTable()
{
    Array *arr = (Array *)malloc(sizeof(Array));
    if (arr == NULL)
    {
        mallocError("Array");
    }
    
    arr->array = (Row *)calloc(sizeof(Row), INITIAL_SIZE);
    if (arr->array == NULL)
    {
        mallocError("Array");
    }

    arr->size = INITIAL_SIZE;
    arr->used = 0;

    return arr;
}

void addToDynamicTable(Array *table, Row *newRow)
{
    if (table->used >= table->size)
    {
        table->size += INITIAL_SIZE;
        table->array = realloc(table->array, sizeof(Row) * table->size);
    }
    table->array[table->used] = *newRow;
    table->used++;
}

void addRowToDynamicTable(Array *table, int address, Int12 value, char ARE)
{
    Row *row = ralloc();

    row->address = address;
    row->value = value.value;
    row->ARE = ARE;
    addToDynamicTable(table, row);
}