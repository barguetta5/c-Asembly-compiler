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
    char *ptr2;
    int i = 0,j;
    int spacesCounter;

    buffer = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    ptr = buffer;
    ptr2 = buffer;

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
            else if (strstr(line, ";") == 0 && line [0] != '\n')
            {
                while (line[i]!='\n')
                {
                    if (line[i] == '\t')
                    {
                        if (i != 0)
                        {
                            line[i] = ' ';
                        }
                        else if (i==0)
                        {
                            for (i = -1; line[i+1]!='\n'; i++)  
                            {  
                                line[i] = line[i+1]; // assign arr[i+1] to arr[i]  
                            }  
                            line[i] = ' ';
                        }
                    }
                    else if (line[i] == ' ')
                    {
                        j = 0;
                        if (i == 0)
                        {
                            while (line[i] == ' ')
                            {
                                i++;
                            }
                            while (line[i+1] != '\n')
                            {
                                line[j] = line[i];
                                i++;
                                j++;
                            }  
                            line[j] = line[i];
                            line[j+1] = ' ';
                        }
                    }                    
                    i++;
                }
                
                strcpy(ptr,line);
                ptr += strlen(line);
            }  
            i = 0;  
        }
        fclose(fptr);
        fptr =  fopen("bar2.TXT","w"); 
        fprintf(fptr,"%s",buffer);
        fclose(fptr);
    }
    else
    {
        printf("coudnt finde ........");
    }
  } 