#include "getInput.h"
#include "common.h"
#include "errors.h"
#include <string.h>

int currentLine = 0;

char *getLine(FILE *f1)
{
	char c, *line;
	int i=0,j;

	if((c=fgetc(f1)) == EOF)
		return NULL;

	line = (char *)malloc(MAXLINE*sizeof(char));
	if(line != NULL)
	{
		if(c!=' ' && c!='\t' && c!='\n')
			line[i++]=c;
		for( j=0 ; i+j<MAXLINE ; i++)
		{
			c = fgetc(f1);
			if(c != EOF && c != '\n')
				line[i] = c;
			else
			{
				line[i]='\0';
				break;
			}
			if (c==' ' || c=='\t') /*sequance of any number of white characters become one space, and if there is a comma it replaces this space*/
			{
				line[i++]=' ';
				c = skipBlanks(f1,&j);
				if(c==',')
				{
					i--;
					j++;
					line[i++] = c;
					line[i++] = (c = skipBlanks(f1,&j));
				}
			}
		}
		line[i] = '\0';

		if(i+j < MAXLINE && c!= EOF && c != '\n')
		{
			c = fgetc(f1);
			while((c = fgetc(f1)) != EOF && c != '\n')
				;
			return "Error. Line is too long";
		}
		else
			return line;
	}
	else
	{
		mallocError("string");
		return "";
	}	
}

char *readLine(FILE *file)
{
	int i,c;
	char *line, *index;

	if ((c = fgetc(file)) == EOF)
	{
		return NULL;
	}
	else
	{
		ungetc(c, file);
	}
	
	line = (char *)calloc(sizeof(char), MAXLINE + 1);
	if (line == NULL)
	{
		mallocError("string");
	}
	index = line;
	i=1;
	for (i = 1;(c = fgetc(file)) != EOF; i++) 
	{
		if (i > MAXLINE)
		{
			printf("Line %d is too long\n", ++currentLine);
			exit(2);
		}
		
		if (c != '\n')
		{
			*index = c;
			index++;
		}
		else
		{
			*index = '\0';
			currentLine++;
			return line;
		}
	}
	*index = '\0';
	currentLine++;
	return line;
}

char skipBlanks(FILE *f1, int *skipped)
{
	char c;
	while((c = fgetc(f1)) && ( c==' ' || c=='\t'))
	    (*skipped)++;
	return c;
}

FILE *openFile(char *fileName)
{
	FILE *pf;
	char *fullFileName;
	char ending[] = ".as";
	printf("checkpoint1\n");
	fullFileName = (char *)malloc(sizeof(fileName) + sizeof(ending));
	if (fullFileName == NULL)
	{
		mallocError("string");
	}
	
	fullFileName[0] = '\0';

	strcat(fullFileName, fileName);
	strcat(fullFileName, ending);
	printf("checkpoint2\n");
	pf = fopen(fullFileName, "r");
	printf("checkpoint3\n");
	if (pf == NULL)
	{
		printf("An error occured when trying to read the file filename");
		exit(2);
	}
	free(fullFileName);
	printf("checkpoint4\n");
	return pf;
}

void deleteBlanks(char *line)
{
	char tmp[MAXLINE];
	int i=0, j;
	for (j=0 ; j<MAXLINE && line[j]!='\0' ; j++)
		if(line[j]!=' ' && line[j]!='\t')
			tmp[i++]=line[j];
		else if(i==0 || tmp[i-1]==',' || line[j+1]==',' || tmp[i-1]==' ')
				;
		else
			tmp[i++]=' ';
	tmp[i]='\0';
	strcpy(line, tmp);
}