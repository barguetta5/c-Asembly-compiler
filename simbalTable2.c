#include <stdio.h>
#include <stdlib.h>
#include "node.c"
#define lengthLine 81
static int arrayLength = 0;
static int ic = 100;
static int dc = 0;
static int sz;
static index = 0;

char *fileToArray(FILE *fptr,node_t *table);
void insertLabel(char *arrayFile,node_t *table);
int sizeOfFile(int sz,FILE *fptr);
int existLable(char lable[30],char lables[30][30]);
void main()
{
    FILE *fptr;
    char *ptr;
    node_t *table;
    fptr = fopen("bar2.txt","r");
    sz = sizeOfFile(sz,fptr);
    ptr = fileToArray(fptr,table);
    fclose(fptr);
}
int sizeOfFile(int sz,FILE *fptr)//the size of the file
{
    fseek(fptr, 0L, SEEK_END);
    sz = ftell(fptr);
    return sz;
}
char *fileToArray(FILE *fptr,node_t *table) 
  {
    char line[lengthLine];
    char *buffer;
	char *ptr;
    int i = 0,j;

    buffer = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    ptr = buffer;

    fptr = fopen("bar2.TXT","r");
    while (!feof(fptr))
    {
        fgets(line,lengthLine,fptr);
        strcpy(ptr,line);
        ptr += strlen(line);
        
    }
    fclose(fptr);
    fptr =  fopen("bar2.TXT","w");
    fprintf(fptr,"%s",buffer);
    fclose(fptr);
    insertLabel(buffer,table);
    return buffer;
  } 
void insertLabel(char *arrayFile,node_t *table)//get the file in array
{
    int i = 0, j = 0;
    int base ,offset;
    char *lable;
    lable = (char*)malloc(30);
    int code;
    for (i = 0; i < sz; i++)
    {
        base = (ic-(ic%16));
        offset = (ic%16);
        j = 0;
        code = 0;
        memset(lable,0,30);
        if (arrayFile[i] == '.' && arrayFile[i+1] == 'e'&& arrayFile[i+2] == 'x')//finde entry lable
        {
            ic = 100;
            while (arrayFile[i] != ' ')//get to the space after the word
            {
                i++;
            }
            i++;// pass the space
            while (arrayFile[i] != '\n')//insert label
            {
                lable[j] = arrayFile[i];
                j++;
                i++;
            }   
            lable[j] = 0;
            for (j = 0; j <5 ; j++)//check if work
            {
                 printf("%c",lable[j]);
            }
            code = 1;
            printf("  value - %d  base - %d  offset - %d ,code - %d\n",0,0,0,1);
        }
        else if (arrayFile[i] == '.' && arrayFile[i+1] == 'e'&& arrayFile[i+2] == 'n')//finde entry lable
        {
            while (arrayFile[i] != ' ')//get to the space after the word
            {
                i++;
            }
            i++;// pass the space
            while (arrayFile[i] != '\n')//insert label
            {
                lable[j] = arrayFile[i];
                j++;
                i++;
            }   
            lable[j] = 0;
            for (j = 0; j <6 ; j++)//check if work
            {
                 printf("%c",lable[j]);
            }
            code = 1;
            printf("  value - %d  base - %d  offset - %d ,code - %d\n",ic,base,offset,code);
        }  
        else if (arrayFile[i] == ':')
        {
            if(arrayFile[i+2] == '.')
                code = 3;
            else
                code = 4;

            while (arrayFile[i] != '\n' && i != 0)//return to the first latter in the word
            {i--;}
            if(i!=0)
                i++;
            while (arrayFile[i] != ':'){
                lable[j] = arrayFile[i];
                j++;
                i++;
            }
            lable[j] = 0;
            for (j = 0; j <6 ; j++){
                 printf("%c",lable[j]);
            }
            printf("  value - %d  base - %d  offset - %d ,code - %d\n",ic,base,offset,code);
            
        }
        if (arrayFile[i] == ' ')
        {
            ic++;
        }
        
    }
    printNode(table);
}
int existLable(char lable[30],char lables[30][30])
{
    int i;
    int boolean = 0;
    for (i = 0; i < index; i++)
    {
        if (strcmp(lable,lables[i])!=0)
        {
            boolean = 1;
        }
    }
    if (boolean == 0)
    {
        strcpy(lables[index],lable);
    }
    return boolean;
}