#include "output.h"

void createFiles(List *codeList, Symbols *symbolsList, Symbols *externalsList, int ICF, int DCF, char *fileName)/*create the machine code files and free data lists*/
{
    FILE *entFile, *extFile, *objFile;
    List *codeListForFree;
    Symbols *symbolsListForFree, *externalsListForFree;
    int isEnt = 0, isExt = 0; 

    objFile = CreateFile(fileName, ".ob");

    /*print .ob file*/

    fprintf(objFile, "%d %d\n", ICF - 100, DCF);
    codeListForFree = codeList;
    while (codeList->next != NULL)
    {
        fprintf(objFile, "%04d %03X %c\n", codeList->value.address, intTo12BitInt(codeList->value.value), codeList->value.ARE);

        /*free previous node*/
        codeList = codeList->next;
        free(codeListForFree);
        codeListForFree = codeList;
    }
    free(codeList);
    fclose(objFile);

    symbolsListForFree = symbolsList;

    /*print .ent file*/
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
        }    
        /*free previous node*/   
        symbolsList = symbolsList->next;
        free(symbolsListForFree->name);
        free(symbolsListForFree->attributes);
        free(symbolsListForFree);
        symbolsListForFree = symbolsList;
    }
    free(symbolsList);

    if (entFile != NULL)
    {
        fclose(entFile);
    }

    externalsListForFree = externalsList;

    /*print .ext file*/
    while (externalsList->next != NULL)
    {

        if (!isExt)
        {
            extFile = CreateFile(fileName, ".ext");
            isExt = 1;
        }

        fprintf(extFile, "%s %04d\n", externalsList->name, externalsList->value.value);

        /*free previous node*/   
        externalsList = externalsList->next;
        free(externalsListForFree->name);
        free(externalsListForFree->attributes);
        free(externalsListForFree);
        externalsListForFree= externalsList;
    }  
    free(externalsList);
    
    if (extFile != NULL)
    {
        fclose(extFile);
    }
        
}


FILE *CreateFile(char *fileName, char *extention)/*create a new file with specified name and extention*/
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
    free(fullFileName);
    return file;
}