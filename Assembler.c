#include <stdio.h>
#include "firstRun.h"

extern int currentLine;

int main(int argc, char *argv[]) {

   if (argc > 1)
   {
      int i, IC=0, ICF=0,DC=0, DCF=0, flags[1]={0};
      for (i = 1; i < argc; i++)
      {
         FILE *inputFile;
         char *line;
         inputFile = openFile(argv[i]);

         while ((line = getLine(inputFile/*, &IC, &DC, &DCF, flags*/)) != NULL)
         {
            printf("Line\t%d:\t", currentLine);
            printf("%s\n", line);
            free(line);
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