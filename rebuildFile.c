#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define lengthLine 81
void *setLine(char line[lengthLine]);
  void main() 
  {
    FILE *fptr;
    char line[lengthLine];
    char *buffer;
	char *ptr;
    int i,j;
    int spacesCounter;

    buffer = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    ptr = buffer;

    fptr = fopen("bar2.TXT","r");

    if (fptr != NULL)
    {
        while (!feof(fptr))
        {
            fgets(line,lengthLine,fptr);
            if (line[0] == '\n')
            {
                while (line[0] != '\n')
                {
                    fgets(line,lengthLine,fptr);
                }
            }
            if (strstr(line, ";") == 0&&line [0] != '\n')
            {
                strcpy(ptr,line);
                ptr += strlen(line);
            }
            
        }
        fclose(fptr);
        for ( i = 0; i < 50; i++)
        {
            if (buffer[i] == '\t')
            {
                    buffer[i] = ' ';     
            }  
            if (buffer[i] == ' ' &&buffer[i+1] == ' ' )
            {
                j = i;
                j++;
                buffer[i] = buffer[j];
                i++;          
            }  
            printf("%c",buffer[i]);      
        }
        
        fptr =  fopen("bar2.TXT","w");
        fprintf(fptr,"%s",buffer);
        fclose(fptr);
    }
    else
    {
        printf("coudnt finde ........");
    }


  } 
