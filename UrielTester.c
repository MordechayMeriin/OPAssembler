#include <stdio.h>
/*#include "firstRun.h"*/
#include "getInput.c"
#include "common.c"


int main(int argc, char *argv[]) {

   int currentLine=0, i, IC=0, ICF=0,DC=0, DCF=0, flags[1]={0};
   printf("cp1\n");
   if (argc > 1)
   {
      printf("cp2\n");
      for (i = 1; i < argc; i++)
      {
         printf("cp3+%d\n", i);
         FILE *inputFile;
         char *line;
         inputFile = fopen("valid.as", "r");
         printf("cp5+%d",i);
         line=getLine(inputFile);
         while (line != NULL)
         {
            printf("cp4+%d\n", currentLine);
            printf("Line\t%d:\t", currentLine);
            printf("%s\n", line);
            free(line);
            currentLine++;
            line=getLine(inputFile);
         }
         
         free(inputFile);
      }   
   }
   else
   {
      printf("No arguments were passed. Please specify the \".as\" files to assemble.\n");
      exit(1);
   }
   return 0;
}