#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inToFile(FILE *nFile,char c);
void rebuild();
void main()
{
    rebuild();
}
void rebuild()
{
    FILE *fptr;
    FILE *nFile;
    char c;
    int i = 0;
    fptr = fopen("bar2.txt","r");
    nFile = fopen("bar3.txt","w");
    while ((c = fgetc(fptr))!= EOF)
    {
        if (i == 0 && c == '\n')
        {
            if ((c = fgetc(fptr))== EOF)
            {
                break;
            } 
        }
        else if (c == '\n')
        {
            i = 0;
        }
        else if(c == ';')
        {
            while ((c = fgetc(fptr))!= EOF && c!='\n')
            {i++;}
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
            inToFile(nFile, c);
            while ((c = fgetc(fptr))!= EOF && c!='\n' && (c == ' ' || c == '\t'))
            {i++;}
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