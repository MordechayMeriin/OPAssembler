#include "getInput.h"

char *getLine(FILE *f1)
{
	char c, *line;
	int i,j;

	if((c=getc(f1)) == EOF)
		return NULL;
	line = (char *)malloc(MAXLINE*sizeof(char));
	if(line)
	{
       line[0]=c;
		for(i=1, j=0 ; i+j<MAXLINE ; i++)
		{
			c = getc(f1);
			if(c != EOF && c != '\n')
				line[i] = c;
			if (c==' ' || c=='\t') /*sequance of any number of white characters become one space, and if there is a comma it replaces this space*/
			{
				line[i++]=' ';
				c = skipBlanks(f1,&j);
				if(c==',')
				{
					i--;
					j++;
					line[i++] = c;
					line[i++] = c = skipBlanks(f1,&j);
				}
			}
		}
		line[i] = '\0';

		if(i+j < MAXLINE && c!= EOF && c != '\n')
		{
			c = getc(f1);
			while((c = getc(f1)) != EOF && c != '\n')
				;
			return "Error. Line is too long\0";
		}
		else
			return line;
	}
	else
	{
		return "Error. Allocation error\0";
	}	
}

char skipBlanks(FILE *f1, int *skipped)
{
	char c;
	while(c = getc(f1) && isspace(c))
	    *skipped++;
	return c;
}