#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedefSimble.c"

#define lengthLine 81

static simbls tab[15];//array of all the simbles
static int simbCount = 0;
static int arrayLength = 0;
static int ic = 100;
static int dc = 0;
static int sz;
static int indexExtern = 0;
static int indexEntry = 0;


char *fileToArray();
void checkFuncInArray(char array[80]);
void insertLabel(char *arrayFile);
int sizeOfFile(int sz);
void icPlus(char line[80]);
int existLable(char lable[30],char lables[30][30]);



int sizeOfFile(int sz)//the size of the file
{
    FILE *fptr;
    fptr = fopen("bar2.TXT","r");
    fseek(fptr, 0L, SEEK_END);
    sz = ftell(fptr);
    fclose(fptr);
    return sz;
}
char *fileToArray() //convert file to array buffer
  {
    FILE *fptr;
    char line[lengthLine];
    char *buffer;
	char *ptr;
    int i = 0,j;
    
    fptr = fopen("bar2.TXT","r");
    sz = sizeOfFile(sz);
    buffer = (char*)malloc(1000*sizeof(char));
    memset(buffer,0,1000*sizeof(char));
    ptr = buffer;
    while (!feof(fptr))
    {
        fgets(line,lengthLine,fptr);
        strcpy(ptr,line);
        ptr += strlen(line);
    }
    //printf("%s",buffer);
    fclose(fptr);
    // fptr =  fopen("bar2.TXT","w");
    // fprintf(fptr,"%s",buffer);
    // fclose(fptr);
    insertLabel(buffer);//mybe this is the problam
    return buffer;
  } 
void insertLabel(char *arrayFile)//get the file in array
{ 
    
    FILE *fptr;
    fptr = fopen("bar2.txt","r");
    int i = 0, j = 0;
    int icIndex = 0;
    int base ,offset;
    char *lable;
    char icLine[80];
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
            while (arrayFile[i] != ' ')//get to the space after the word
            {
                i++;
            }
            i++;// pass the space
            while (arrayFile[i] != '\n' && i<sz)//insert label
            {
                lable[j] = arrayFile[i];
                j++;
                i++;
            }  
            lable[j] = 0;
            if(!exist(tab,lable,simbCount,code,ic,base,offset))
            {    strcpy(tab[simbCount].lab,lable);
                tab[simbCount].value = 0;
                tab[simbCount].base = 0;
                tab[simbCount].offset = 0;
                tab[simbCount].atr[0] = 0;
                simbCount++;
            }

        }
        else if (arrayFile[i] == '.' && arrayFile[i+1] == 'e'&& arrayFile[i+2] == 'n')//finde entry lable
        {
            while (arrayFile[i] != ' ')//get to the space after the word
            {
                i++;
            }
            i++;// pass the space
            while (arrayFile[i] != '\n'&&arrayFile[i] != ' ')//insert label
            {
                lable[j] = arrayFile[i];
                j++;
                i++;
            }   
            lable[j] = 0;
            code = 1;
            if(!exist(tab,lable,simbCount,code,ic,base,offset))
                { strcpy(tab[simbCount].lab,lable);
                tab[simbCount].value = ic;
                tab[simbCount].base = base;
                tab[simbCount].offset = offset;
                tab[simbCount].atr[0] = code;
                simbCount++;
                }
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
            if(!exist(tab,lable,simbCount,code,ic,base,offset))
            { strcpy(tab[simbCount].lab,lable);
            tab[simbCount].value = ic;
            tab[simbCount].base = base;
            tab[simbCount].offset = offset;
            tab[simbCount].atr[0] = code;
            simbCount++;
            }
        }
        if (arrayFile[i]=='\n')
        {
            fgets(icLine,80,fptr);
            icPlus(icLine); 
        }
    }
    fclose(fptr);
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
    else
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
            if (strstr(firstOp,"#") &&strstr(secondtOp,"#"))
            {
                ic+=4;
                return ;
            }
            else if (strstr(firstOp,"#") ||strstr(secondtOp,"#"))
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
            
            if (array[5]>=65 &&array[5]<=122 &&array[5]!='r')
            {
                 ic+=4;
                return ;
            }
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
        i = 3;
        while (array[i] != 'i'&&array[i+1] != 'n'&&array[i+2] != 'g')
        {
            i++;
        }
        i+=5;
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
    else if (strstr(array,".extern")||strstr(array,".entry"))
    {
        return;
    }
    
    ic+=1;
    return ;
}
