#include <stdio.h>
#include "firstRun.h"

int main(int argc, char *argv[]) 
{
   int i;
   if (argc > 1)
   {
      for (i = 1; i < argc; i++)
      {
         first(argv[i]);
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