#include "getInput.h"

char *getLine(FILE *f1)
{
	char c, *line;
	int i;

	if((c=getc(f1)) == EOF)
		return NULL;
	line = (char *)malloc(MAXLINE*sizeof(char));
	if(line)
	{
       line[0]=c;
		for(i=1 ; c = getc(f1) != EOF && c != '\n' && i<(MAXLINE-1) ; i++)
			line[i] = c;
		line[i] = '\0';

		if(i < MAXLINE && c!= EOF && c != '\n')
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

int skipBlanks(char *line, int index)
{
	char c;
	for(c = line[index] ; c != '\0' && isspace(c) ; index++)
	    ;
	return index;
}