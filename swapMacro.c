#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macroNode.c"


// int lengthLine1 = 81;
// int sizeName = 30;

void findeMacro(Node *head,char nameFile[30]);
void replaceMacro(Node *head,char newNameFile[30]);

// int main(void)
// {
//     Node *head = NULL;
//     findeMacro(head,"macro.as");
//     return 0;
// }

void findeMacro(Node *head,char newNameFile[30]) //convert file to array buffer
  {
    FILE *fptr;
    char line[81];
    char *buffer;
	char *ptr;
    char *word;
    char *macroLines;
    int i = 0,j = 0;
    
    fptr = fopen(newNameFile,"r");
    buffer = (char*)malloc(1000*sizeof(char));
    word = (char*)malloc(30);
    macroLines = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    memset(macroLines,0,81*5);
    memset(word,0,30);
    ptr = buffer;
    while (!feof(fptr))
    {
        fgets(line,81,fptr);
        if (strstr(line,"macro"))
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
            fgets(line,81,fptr);
            while (!strstr(line,"endm"))
            {
                strcat(macroLines,line);
                fgets(line,81,fptr);
            }
            insert(&head, word,macroLines);
            memset(word,0,30);
            memset(macroLines,0,81*5);
        }   
    }
    
    fclose(fptr);
    free(buffer);
    free(word);
    free(macroLines);
    replaceMacro(head,newNameFile);
    
  } 
void replaceMacro(Node *head,char newNameFile[30])
  {
    FILE *fptr;
    char line[81];
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
        fgets(line,81,fptr);
        if (strstr(line,"macro"))
        {
            while (!strstr(line,"endm"))
            {
                fgets(line,81,fptr);
            }
            fgets(line,81,fptr);
            
        }
        if (macroExist(head,line)!=0)
        {
            strcpy(ptr,head->line);
            //printf("%s\n\n",ptr);
            ptr += strlen(head->line);
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