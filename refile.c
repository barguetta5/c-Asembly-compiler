#include <stdio.h>
#include <stdlib.h>

void readFileToArray(char copyFile[50][50],FILE *fptr);
int main()
{
    FILE *fptr;
    char copyFile[50][50];
    readFileToArray(copyFile,fptr);
    fclose(fptr);
    return 0;

   
}
void readFileToArray(char copyFile[50][50],FILE *fptr)
{
    char filename[30] = "b.txt";
    char c;
    int i = 0,j=0;
    int saveSpace = 0;
  
  
    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
  
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        //printf ("%c", c);
        if(c == '\n')
        {
            if(j !=0)
                {
                    copyFile[i][j] = c;
                    i++;
                }
            j = 0;  
            c = fgetc(fptr); 
        }
        else if (j!=0 && c==' ')
        {
            
            copyFile[i][j] = c;
            j++;
            while (c == ' ')
            {
                c = fgetc(fptr);
            }
            if(c == '\n')
            {
                if(j !=0)
                    {
                        copyFile[i][j] = c;
                        i++;
                    }
                j = 0;   
            }
            else
                {
                    copyFile[i][j] = c;
                    j++;
                    c = fgetc(fptr);
                }
        }
        else if (j==0 && c==' ')
        {
            while (c == ' ')
            {
                c = fgetc(fptr);
            }
            if(c == '\n')
            {  
                c = fgetc(fptr);
            }
            else
            {
                copyFile[i][j] = c;
                j++;
                c = fgetc(fptr);
            }

        }
        else if (c == ';')
        {
            while (c !='\n'&& c !=EOF)
            {
                c = fgetc(fptr);
            }
            c = fgetc(fptr);
        }
        else if(c == '\n')
        {
            copyFile[i][j] = c;
            j==0;
            i++;
            c = fgetc(fptr);
        }
        else
        {
            copyFile[i][j] = c;
            j++;
            c = fgetc(fptr);
        }
    }

    printf("%s", copyFile[1]);
}