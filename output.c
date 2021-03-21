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

void createFiles(List *codeList, Symbols *symbolsList, Symbols *externalsList, int ICF, int DCF, char *fileName)
{
    FILE *entFile, *extFile, *objFile;
    int isEnt = 0, isExt = 0; 

    objFile = CreateFile(fileName, ".obj");

    fprintf(objFile, "%d %d\n", ICF - 100, DCF);
    printf("%d %d\n", ICF - 100, DCF);/*Debug*/

    while (codeList->next != NULL)
    {
        fprintf(objFile, "%04d %03X %c\n", codeList->value.address, intTo12BitInt(codeList->value.value), codeList->value.ARE);
        printf("%04d %03X %c\n", codeList->value.address, intTo12BitInt(codeList->value.value), codeList->value.ARE);
        codeList = codeList->next;
    }
    fclose(objFile);

    while (symbolsList->next != NULL)
    {
        if (symbolsList->attributeList.entry)
        {
            if (!isEnt)
            {
                entFile = CreateFile(fileName, ".ent");
                isEnt = 1;
            }
            
            fprintf(entFile, "%s %04d\n", symbolsList->name, symbolsList->value.value);
            printf("Ent: %s %04d\n", symbolsList->name, symbolsList->value.value);/**Debug*/           
        }       
        symbolsList = symbolsList->next;      
    }

    if (entFile != NULL)
    {
        fclose(entFile);
    }

    while (externalsList->next != NULL)
    {

        if (!isExt)
        {
            extFile = CreateFile(fileName, ".ext");
            isExt = 1;
        }

        fprintf(extFile, "%s %04d\n", externalsList->name, externalsList->value.value);
        printf("Ext: %s %04d\n", externalsList->name, externalsList->value.value);/**Debug*/

        externalsList = externalsList->next;
    }  
    
    if (extFile != NULL)
    {
        fclose(extFile);
    }
        
}


FILE *CreateFile(char *fileName, char *extention)
{
    FILE *file;
    char *fullFileName = (char *)calloc(sizeof(char), strlen(fileName) + strlen(extention) + 1);

    if (fullFileName == NULL)
    {
        mallocError("string");
    }
    
    strcpy(fullFileName, fileName);
    strcat(fullFileName, extention);

    file = fopen(fullFileName, "w");
    if (file == NULL)
    {
        printf("Error: could not create the file %s.\n", fullFileName);
        exit(2);
    }
    return file;
}