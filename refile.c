#include <stdio.h>
#include <stdlib.h>
#include "compiler.c"

#define LSIZ 80 
#define RSIZ 30 
static char line[RSIZ][LSIZ];
static int length;
void readFileToArray2();
void arraySet();
//void readFileToArray();
int main()
{
    int i;
    readFileToArray2();
    arraySet();

//    for( i = 0; i < 4; ++i)
//     {
//         printf(" %s\n", line[i]);
//     }
//     printf("\n");
   return 0;
}
void readFileToArray2()
{
    
	char fname[20] = "bar2.txt";
    FILE *fptr = NULL; 
    int i = 0;
    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        // line[i][strlen(line[i]) - 1] = '\0';
        i++;
           
    }
    length = i;
}
void arraySet()
{
    int i = 0;
    int j;
    char newLine[RSIZ][LSIZ];
    while (i < length)
    {
        for (j = 0;j<(strlen(line[i])-1);j++)
        {
            if (line[i][j]!= '\0' && line[i][j]!= '\n')
            {
                newLine[i][j] = line[i][j];
            }    
        }
        i++;
    }
    for( i = 0; i < 4; ++i)
    {
        printf(" %s\n", newLine[i]);
    }
    printf("\n");
}
// }
// void readFileToArray()
// {
//     FILE *f;
//     int i = 0,j = 0;
//     int c;
//     char arr[50][50];

//     f = fopen("bar2.txt", "r");
//     while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\t' || c == '\n'));//pass the first line

//     while (c != EOF) {
//         printf("%c",c);
//     if (c == ' ' || c == '\t' || c == '\n' || c == ';') {
//         if (c == '\n') {
//         arr[i][j] = '\0';
//         i++; j = 0;
//         }if (c == ';')
//         {
//            while (c != EOF && c != '\n')
//            {
//                c = fgetc(f);
//            }
//         }
//         else {
//         arr[i][j] = ' ';
//         j++;
//         }
//         while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\t' || c == '\n'));
//         continue;
//     }
//     arr[i][j] = (char)c;
//     j++;
//     c = fgetc(f);
//     }
//     i++;
//     arr[i][0] = '\0';
//     arr[i][1] = '\0';
//     i = 0;
//     j = 0;
//     // while (arr[i][0] != '\0'&&arr[i][1] != '\0') {
//     //  printf("line %d\n",i);
//     // while (arr[i][j] != '\0') {
//     //     printf("%c",arr[i][j]);
//     //     j++;
//     // }
//     // printf("\n");
//     // i++;
//     //}
// }
