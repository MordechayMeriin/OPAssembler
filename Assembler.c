#include <stdio.h>
#include "firstRun.h"

/*extern int currentLine;*/
int  IC = 100, DC = 0, ICF, DCF; /*global vars*/

int main(int argc, char *argv[]) 
{
   int i;
   if (argc > 1)
   {
      for (i = 1; i < argc; i++)
      {
         FILE *inputFile;
         inputFile = openFile(argv[i]);
         first(inputFile);

         free(inputFile);
      }
      return 0;   
   }
   else
   {
      printf("No arguments were passed. Please specify the \".as\" files to assemble.\n");
      exit(1);
   }
   return 0;
}