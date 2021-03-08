#include <stdio.h>
#include "firstRun.h"

/*extern int currentLine;*/
int  IC = 100, DC = 0, L ,ICF,DCF; /*global vars*/

int main(int argc, char *argv[]) 
{
   int i;
   if (argc > 1)
   {
      for (i = 1; i < argc; i++)
      {
         FILE *inputFile;
         char *line = calloc(sizeof(char), 81);
         inputFile = openFile(argv[i]);
         /*here comes first-run, right? instead of the 'while' that comes next*/


         while ((fgets(line, 81, inputFile)) != NULL)
         {
            printf("%s\n", line);
            /*free(line);*/
         }
         free(line);
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