#include <stdio.h>
#include <stdlib.h>
#include "printBinry.c"

void entryFile();
void main()
{
    int i;
    char *line = (char*)malloc(80*sizeof(char));
    char *ptr;
    ptr   = fileToArray();
    codeToBinary(line,ptr);
    // for (i = 0; i < simbCount; i++)
    // {
    //     printTable(tab[i]);
    // }
    entryFile();
}
void entryFile()//pass after all the tabs and print in new file the entry simblse
{
    FILE *newF;
    int i;
    newF = fopen("ps.ent","w");
     for (i = 0; i < simbCount; i++)
    {
        if (tab[i].atr[0] == 1 || tab[i].atr[1] == 1)
        {
            fprintf(newF,"%s,%d,%d\n",tab[i].lab,tab[i].base,tab[i].offset);
        }
    }
    fclose(newF);
}
