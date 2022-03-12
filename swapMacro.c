#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macroNode.c"


#define lengthLine1  81
#define  sizeName  30

void findeMacro(Node *head,char nameFile[sizeName]);
void replaceMacro(Node *head,char newNameFile[sizeName]);


void findeMacro(Node *head,char newNameFile[sizeName])
  {
    FILE *fptr;
    char line[lengthLine1];
    char *buffer;
	char *ptr;
    char *word;
    char *macroLines;
    int i = 0,j = 0;
    
    fptr = fopen(newNameFile,"r");
    buffer = (char*)malloc(1000*sizeof(char));
    word = (char*)malloc(sizeName);
    macroLines = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    memset(macroLines,0,lengthLine1*5);
    memset(word,0,sizeName);
    ptr = buffer;
    while (!feof(fptr))
    {
        fgets(line,lengthLine1,fptr);
        if (strstr(line,"macro"))//check if there is macro in and line and save the name of it
        {
            i = 6 ;
            while (line[i] != '\n'&& line[i] != ' ')
            {
                word[j] = line[i];
                i++;
                j++;
            }
            word[j] = '\0';
            j = 0;
            fgets(line,lengthLine1,fptr);
            while (!strstr(line,"endm")) // insert macro's lines
            {
                strcat(macroLines,line);
                fgets(line,lengthLine1,fptr);
            }
            insert(&head, word,macroLines);
            memset(word,0,sizeName);
            memset(macroLines,0,lengthLine1*5);
        }   
    }
    fclose(fptr);
    free(buffer);
    free(word);
    free(macroLines);
    replaceMacro(head,newNameFile);
    
  } 
void replaceMacro(Node *head,char newNameFile[sizeName])
  {
    FILE *fptr;
    char line[lengthLine1];
    char *buffer;
	char *ptr;
    int i = 0,j;

    fptr = fopen(newNameFile,"r");
    buffer = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    ptr = buffer;
    //printList(head);
    while (!feof(fptr))
    {
        fgets(line,lengthLine1,fptr);
        if (strstr(line,"macro"))
        {
            while (!strstr(line,"endm"))
            {
                fgets(line,lengthLine1,fptr);
            }
            fgets(line,lengthLine1,fptr);
            
        }
        if (macroExist(head,line)!=NULL)
        {
            strcpy(ptr,macroExist(head,line));
            //printf("%s\n\n",ptr);
            ptr += strlen(macroExist(head,line));
            //printf("%s\n\n",ptr);
        }
        else
        {
            strcpy(ptr,line);
            ptr += strlen(line);
            //printf("%s\n\n",ptr);
        }
    }
    //printf("%s",buffer);
    //fclose(fptr);
    fptr =  fopen(newNameFile,"w");
    fprintf(fptr,"%s",buffer);
    fclose(fptr); 
    // free(ptr);
    // free(buffer);     
  }