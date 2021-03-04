#include <stdio.h>
#include "header.h"

/*extern int currentLine;*/
int  IC=0, ICF=0,DC=0, DCF=0, flags[2]={0,0}; /*global vars, flags[0] signals if there is a label, flags[1] errors*/

int main(int argc, char *argv[]) {
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
   }
   else
   {
      printf("No arguments were passed. Please specify the \".as\" files to assemble.\n");
      exit(1);
   }
   return 0;
}