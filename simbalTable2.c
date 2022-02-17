#include <stdio.h>
#include <stdlib.h>
#include "typedefSimble.c"
#define lengthLine 81
static int arrayLength = 0;
static int ic = 100;
static int dc = 0;
static int sz;
static int indexExtern = 0;
static int indexEntry = 0;
static lables[30][30];
static externArray[30][30];
static entryArray[30][30];

char *fileToArray(FILE *fptr);
int checkOgerInArray(char array[80]);
int countCommon(char array[80]);
void checkFuncInArray(char array[80]);
void insertLabel(char *arrayFile);
int sizeOfFile(int sz,FILE *fptr);
void icPlus(char line[80]);
int existLable(char lable[30],char lables[30][30]);
void main()
{
    FILE *fptr;
    char *ptr;
    int i = 0;
    char line[80];
    fptr = fopen("bar2.txt","r");
    sz = sizeOfFile(sz,fptr);
    ptr = fileToArray(fptr);
    for (i = 0; i < 30; i++)
    {
        printf("%s\n",lables[i]);
    }
    fclose(fptr);
    //printf("%d",icPlus(" LOOP: prn #48 "));
}
int sizeOfFile(int sz,FILE *fptr)//the size of the file
{
    fseek(fptr, 0L, SEEK_END);
    sz = ftell(fptr);
    return sz;
}
char *fileToArray(FILE *fptr) //convert file to array buffer
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
    insertLabel(buffer);
    return buffer;
  } 
void insertLabel(char *arrayFile)//get the file in array
{
    int i = 0, j = 0;
    int icIndex = 0;
    int base ,offset;
    char *lable;
    char *icLine;
    icLine = (char*)malloc(80);
    lable = (char*)malloc(30);
    int code;
    printf("%s",icLine);
    printf("%d\n",sz);
    for (i = 0; i < sz; i++)
    {
        if (arrayFile[i]!='\n')
        {
            icLine[icIndex] = arrayFile[i];
            icIndex++;
        }
        else
        {
            printf("%s\n",icLine);
            //icPlus(icLine);
            icLine = memset(icLine,'\0',80);
            icIndex = 0;      
        }
        
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
            strcpy(externArray[indexExtern],lable);
            indexExtern++;
        }
        else if (arrayFile[i] == '.' && arrayFile[i+1] == 'e'&& arrayFile[i+2] == 'n')//finde entry lable
        {
            while (arrayFile[i] != ' ')//get to the space after the word
            {
                i++;
            }
            i++;// pass the space
            ic++;
            while (arrayFile[i] != '\n'&&arrayFile[i] != ' ')//insert label
            {
                lable[j] = arrayFile[i];
                j++;
                i++;
            }   
            lable[j] = 0;
            ic++;
            strcpy(entryArray[indexEntry],lable);
            indexEntry++;
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
            existLable(lable,lables);
        }
        if (arrayFile[i] == ' ')
        {
            ic++;
        }
        
    }
}
int existLable(char lable[30],char lables[30][30])
{
    static int index = 0;
    int i = 0;
    int boolean = 0;
    for (i; i < 10; i++)
    {
        if (strcmp(lable,lables[i])==0)
        {
            boolean = 1;
        }
    }
    if (boolean == 0)
    {
        strcpy(lables[index],lable);
        index++;
    }
    return boolean;
}
void icPlus(char line[80])//pass the : in the text
{
    int i = 0;
    int newL = 0;
    char newLine[80];
    if (strstr(line,":"))
    {
        while (line[i]!=':')
        {
            i++;
        }
        i+=2;//pass the space after ;
        while (line[i]!='\n'){
            newLine[newL] = line[i];
            i++;
            newL++;
        }
           checkFuncInArray(newLine);
    }
      checkFuncInArray(line);
}
void checkFuncInArray(char array[80])//return how many ic i need to add to my counter
{
    char firstOp[30];
    char secondtOp[30];
    int i = 4;
    int index = 0;
    int countC = 1;
    int ogercount = 0;
    if (strstr(array,"mov")||strstr(array,"cmp")||strstr(array,"add")||strstr(array,"sub")||strstr(array,"lea"))
    {
        while (array[i] != ',')
        {
            firstOp[index] = array[i];
            index++;
            i++;
        }
        i+=2;
        index = 0;
        while (array[i] != '\n' && array[i] != ' ')
        {
            secondtOp[index] = array[i];
            index++;
            i++;
        }
        ogercount += checkOgerInArray(firstOp) + checkOgerInArray(secondtOp);
        if(ogercount == 2)
        {
            ic+=2;
            return ;
        }
        else if (ogercount == 1)
        {
            if (strstr(array,"#"))
            {
                ic+=3;
                return ;
            }
            else
            {
                ic+=4;
                return ;
            }
        }
        else
        {
            if (countCommon(array) == 2)
            {
                ic+=4;
                return ;
            }
            else if (countCommon(array) == 1)
            {
                ic+=5;
                return ;
            }
            else
            {
                ic+=6;
                return ;
            }
        }
    }
    else if (strstr(array,"clr")||strstr(array,"not")||strstr(array,"inc")||strstr(array,"dec")||strstr(array,"jmp")
            ||strstr(array,"bne")||strstr(array,"jsr")||strstr(array,"red")||strstr(array,"prn"))
    {
        if(checkOgerInArray(array) == 1)
        {
            ic+=2;
            return ;
        }
        else if (strstr(array,"#"))
        {
            ic+=3;
            return ;
        }
        else
        {
            ic+=4;
            return ;
        }
    }
    else if (strstr(array,".data"))//check the ic of .data
    {
        if (!strstr(array,","))
        {
            ic+=countC;
            return;
        }
        else
        {
            while (array[i]!='\0' &&array[i]!='\n')
            {
                if (array[i]==',')
                {
                    countC ++;
                }
                i++;
            }
        }
        ic+=countC;
        return ;
    }
    else if (strstr(array,".string"))//check the ic of .string
    {
        i = 11;
        while (array[i]>='A'&&array[i]<'z' && array[i]!='\n')
        {
            if (array[i]>='a'&&array[i]<'z')
            {
                 countC++;
            }     
            i++;
        }
        ic+=countC;
        return ;
    }
    ic+=1;
    return ;
}
int checkOgerInArray(char array[80])//check how much ogrim i have got
{
   
    int i = 0;
    static int count;
    count = 0;
    if (strstr(array,"r0")||strstr(array,"r1")||strstr(array,"r2")||strstr(array,"r3")||strstr(array,"r4")
    ||strstr(array,"r5")||strstr(array,"r6")||strstr(array,"r7")||strstr(array,"r8")||strstr(array,"r9")
    ||strstr(array,"r10")||strstr(array,"r11")||strstr(array,"r12")||strstr(array,"r13")||strstr(array,"r14")||strstr(array,"r15"))
    {
            count++;
    }
    return count;
}
int countCommon(char array[80])//check if there is common in the line
{
    int i;
    int counter = 0;
    while (array[i] !='\n')
    {
        if (array[i] == '#')
        {
             counter++;
        }
    }
    return counter;
}