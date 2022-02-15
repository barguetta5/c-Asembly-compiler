#include <stdio.h>
#include <stdlib.h>
#include "compiler.c"

#define LSIZ 80 
#define RSIZ 30 
static char line[RSIZ][LSIZ];
static int length;
void readFileToArray();
int main()
{
    int i;
    readFileToArray();
   for( i = 0; i < 4; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");
   return 0;
}
void readFileToArray()
{
    FILE *f;
    int i = 0,j = 0;
    int c;
    char arr[50][50];

    f = fopen("bar2.txt", "r");
    while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\t' || c == '\n'));//pass the first line

    while (c != EOF) {
        printf("%c",c);
        if (c == ' ' || c == '\t' || c == '\n' || c == ';') {
            if (c == '\n') {
            arr[i][j] = '\0';
            i++; j = 0;
            }
        if (c == ';')
        {
           while (c != EOF && c != '\n')
           {
               c = fgetc(f);
           }
        }
        else {
        arr[i][j] = ' ';
        j++;
        }
        while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\t' || c == '\n'));
        continue;
    }
    arr[i][j] = (char)c;
    j++;
    c = fgetc(f);
    }
    i++;
    arr[i][0] = '\0';
    arr[i][1] = '\0';
    i = 0;
    j = 0;
}
