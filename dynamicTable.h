#ifndef DYNAMIC_TABLE_INCLUDED
#define DYNAMIC_TABLE_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "dataModel.h"
#include "common.h"

typedef struct array
{
    Row *array;
    int used;
    int size;
}Array;

Array *createDynamicTable();

void addToDynamicTable(Array *table, Row *newRow);

void addRowToDynamicTable(Array *table, int address, Int12 value, char ARE);

#endif