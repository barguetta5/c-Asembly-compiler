#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "printHexa.c"
#include "erorFinde.c"
#include "swapMacro.c"


void inToFile(FILE *nFile,char c);
void rebuild(char nameFile[30] , char newNameFile[30]);
void main()
{
    Node *head = NULL;

    char nameFile[30];
    char newNameFile[30];
    char endText[3] = ".as";
    char endNewText[3] = ".ob";
    // printf("please enter name of file withous the type of the file");
    // scanf("%s",&nameFile);
    strcpy(nameFile,"bar");
    strcpy(newNameFile,nameFile);
    strncat(newNameFile,endNewText,3);
    strncat(nameFile,endText,3);

    rebuild(nameFile,newNameFile);//this func from this file
    findeMacro(head,newNameFile);//this func from swapmacro.c
    if (!erorFile(newNameFile))//this func from printHexa.c
    {
        printf("not work");
        exit(0);
    }
    getLine(newNameFile);//this func from printHexa.c
}
void rebuild(char nameFile[30],char newNameFile[30])
{
    FILE *fptr;
    FILE *nFile;
    char c;
    int i = 0;
    fptr = fopen(nameFile,"r");
    nFile = fopen(newNameFile,"w");
    while ((c = fgetc(fptr))!= EOF)
    {
        if (i == 0 && c == '\n')
        {
            if ((c = fgetc(fptr))== EOF)
            {
                break;
            } 
            if (c=='\n')
            {
                while ((c = fgetc(fptr)) && c=='\n' || c==' '|| c=='\t');
            }
        }
        else if (i!=0 && c == '\n')
        {
            i = 0;
        }
        else if(c == ';')
        {
            while ((c = fgetc(fptr))!= EOF && c!='\n')
            {i++;}
            i = 0;
            c = fgetc(fptr);
        }
        else if (c == '\t')
        {
            c = ' ';
            inToFile(nFile, c);
            c = fgetc(fptr);
            i++;
            while ((c = fgetc(fptr))!= EOF && c!='\n' && (c == ' ' || c == '\t'))
            {i++;}
        }
        else if (c == ' ')
        {
            if(i != 0)
                inToFile(nFile, c);
            while ((c = fgetc(fptr))!= EOF && c!='\n' && (c == ' ' || c == '\t'))
            {i++;}
            if (c == '\n')
            {
                i = 0;
            }     
        }
        else
        {i++;} 
        inToFile(nFile, c);
    }

    fclose(fptr);
    fclose(nFile);   
}
void inToFile(FILE *nFile,char c) //this method print to file the binary table 
{    
    fprintf(nFile,"%c",c);
}