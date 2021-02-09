#include "getInput.h"

char *getLine(FILE *f1)
{
	char c, *line;
	int i=0,j;

	if((c=getc(f1)) == EOF)
		return NULL;
	line = (char *)malloc(MAXLINE*sizeof(char));
	if(line)
	{
		if(c!=' ' && c!='\t' && c!='\n')
			line[i++]=c;
		for( j=0 ; i+j<MAXLINE ; i++)
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
			return "Error. Line is too long";
		}
		else
			return line;
	}
	else
	{
		return "Error. Allocation error";
	}	
}

char skipBlanks(FILE *f1, int *skipped) /* you have warnings here */
{
	char c;
	while((c = getc(f1)) && ( c==' ' || c=='\t'))
	    *skipped++;
	return c;
}