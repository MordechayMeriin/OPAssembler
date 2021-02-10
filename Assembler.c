#include <stdio.h>
#include "firstRun.h"

extern int currentLine;

int main(int argc, char *argv[]) {

   if (argc > 1)
   {
      int i;
      for (i = 1; i < argc; i++)
      {
         FILE *inputFile;
         char *line;
         inputFile = openFile(argv[i]);

         while ((line = readLine(inputFile)) != NULL)
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