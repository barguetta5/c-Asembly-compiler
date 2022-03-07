#include <stdio.h>
#include <string.h>

int checkFile(char nameFile[30]);
int checkDot(char nameFile[30]);
int checkColon(char nameFile[30]);
int checkExtEntrLable(char nameFile[30]);
int erorFile(char nameFile[30]);
int checkfunc(char nameFile[30]);
int checkHash(char nameFile[30]);
int sizeLineCheck(char nameFile[30]);
int checkStrDat(char nameFile[30]);
int checkComma(char nameFile[30]);
int funcArguments(char nameFile[30]);
// void main()
// {
//     printf("%d",erorFile());
// }
int erorFile(char nameFile[30])//return if there was an error
{
    int boolean = 1;
    if (!checkFile(nameFile))
    {   
        boolean = 0;
    }
    if (sizeLineCheck(nameFile)>80)
    {    
        boolean = 0;
    }
    if (!checkDot(nameFile))
    {    
        boolean = 0;
    }
    if (!checkColon(nameFile))
    {    
        boolean = 0;
    }
    if (!checkfunc(nameFile))
    {    
        boolean = 0;
    }
    if (!checkHash(nameFile))
    {   
        boolean = 0;
    }
    if (!checkComma(nameFile))
    {   
        boolean = 0;
    }
    if (!checkExtEntrLable(nameFile))
    {    
        boolean = 0;
    }
    if (!funcArguments(nameFile))
    {
        boolean = 0;
    }
     
    if (!checkStrDat(nameFile))
    {   
        boolean = 0;
    }
    return boolean;
    
}
int checkfunc(char nameFile[30])//check if all function write with lower case
{   
    FILE *fp;   
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, "MOV") != 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            }  
            if(strstr(line, "CMP") != 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "ADD")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "SUB")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "LEA")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "CLR")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "NOT")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "INC")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "DEC")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "JMP")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "BNE")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "JSR")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "RED")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "PRN")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "RTS")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            if(strstr(line, "STOP")!= 0)
            {
                printf("eror in line %d: did not write right the function\n",numLine);
                boolean = 0;
            } 
            numLine++;
        }
    fclose(fp);
    return boolean;

}
int checkHash(char nameFile[30])//check no space after " # "
{
    FILE *fp;   
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, "#"))
            {
                if(strstr(line, "# "))
                {
                    printf("eror in line %d: hash have sapce after it\n",numLine);
                    boolean = 0;
                }  
                if(!strstr(line, " #"))
                {
                    printf("eror in line %d: hash have no sapce befor it\n",numLine);
                    boolean = 0;
                } 
            }
            numLine++;
        }
    fclose(fp);
    return boolean;
}
int checkFile(char nameFile[30])//check if file exist
{
    FILE *fp;
    fp = fopen(nameFile,"r"); 
    if(fp == NULL)
    {
        printf(" File does not exist or can not be opened.\n"); 
        return 0;
    }
    fclose(fp);
    return 1;
}
int checkDot(char nameFile[30])//check if after dot there is no space and right name
{
    FILE *fp;    
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, ". ") != 0||strstr(line, ".\n") != 0)
            {
                printf("eror in line %d: DOT with space after it\n",numLine);
                boolean =0 ;
            }  
            if(strstr(line, ".")&&(!strstr(line, ".data")&&!strstr(line, ".string")
            &&!strstr(line, ".entry")&&!strstr(line, ".extern")))
            {
                printf("eror in line %d: use dot without any rigth functions\n",numLine);
                boolean = 0;
            }  
            numLine++;
        }
    fclose(fp);
    return boolean;
}
int checkColon(char nameFile[30])//check that there is no space before " : "
{
    FILE *fp;  
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while ( fgets(line,80,fp) != NULL)
        {
            if( strstr(line, " :") != 0  || (strstr(line, ":") != 0 && strstr(line, ": ") == 0)) 
            {
                printf("eror in line %d: ':' not use right\n",numLine);
                boolean = 0;
            }
            numLine++;
        }
    fclose(fp); 
    return boolean;
}
int sizeLineCheck(char nameFile[30] )//check if there is line bigger then 80
{
    FILE *fp;
    char str[100],longest[100];
    int len = 0;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while(fgets(str,sizeof(str),fp)!=NULL)
    {
        if(len<strlen(str))
        {
            strcpy(longest,str);
            len=strlen(str);
        }
     }
     if (len>81)
     {
         printf("eror in line : the file include lines longer then 80\n");
         return 0;
     }
    fclose(fp); 
    return 1;
}
int checkStrDat(char nameFile[30])//check if string or data write well
{
    FILE *fp;
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r");
    while ( fgets(line,80,fp) != NULL)
        {
            if((strstr(line, ".string")&&!strstr(line, ".string ")) 
            || (strstr(line, ".data") &&!strstr(line, ".data ")) ) 
            {
                
                printf("eror in line %d: .string or .data write without space after it\n",numLine);
                boolean = 0;
            }
            if( strstr(line, ".STRING") != 0  || strstr(line, ".DATA") != 0 ) 
            {
                printf("eror in line %d: .string or .data write in Capital letters\n",numLine);
                boolean = 0;
            }
            
            numLine++;
        }
    fclose(fp);
    return boolean;
}
int checkExtEntrLable(char nameFile[30])
{
    FILE *fp;
    char word[30];
    char wordArray[30][30];
    int getIn = 0;
    int i = 0;
    int j;
    int numLine = 0;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while (!feof(fp))
    {
        fscanf(fp,"%s*[^\n]",word);
        if(strcmp(word,".entry") == 0|| strcmp(word,".extern") == 0)
            {
                getIn = 1;
                fscanf(fp,"%s*[^\n]",word);
                i++;
            }
        if (getIn == 1)
        {
            getIn = 0 ;
            for(j = 0; j < i; ++j)
            {
                if(strcmp(wordArray[j], word) == 0)
                {
                    printf("eror in line %d: Lable cant be use twise\n",numLine);
                    boolean = 0;
                }
            }
            if (boolean == 1)
            {
                strcpy(wordArray[i],word);
                i++;
            }
        }  
        numLine++;
    }
    fclose(fp);
    printf("%d\n",boolean);
    return boolean;
}
int checkComma(char nameFile[30])
{
    FILE *fp;
    char line[80];
    int numLine = 1;
    int boolean = 1;
    fp = fopen(nameFile,"r"); 
    while (!feof(fp))
        {
            fgets(line,80,fp);
            if( strstr(line, ",\n") != 0 ) 
            {   
                printf("eror in line %d: con't be ',' at the end of line\n",numLine);
                boolean = 0;
            }
            else 
            {
                if(strstr(line, "mov ,") != 0||strstr(line, "mov,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                }  
                if(strstr(line, "cmp ,") != 0||strstr(line, "cmp,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "add ,") != 0||strstr(line, "add,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "sub ,") != 0||strstr(line, "sub,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "lea ,") != 0||strstr(line, "lea,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "clr ,") != 0||strstr(line, "clr,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "not ,") != 0||strstr(line, "not,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "inc ,") != 0||strstr(line, "inc,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "dec ,") != 0||strstr(line, "dec,") != 0)
                {
                    boolean = 0;
                } 
                if(strstr(line, "jmp ,") != 0||strstr(line, "jmp,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "bne ,") != 0||strstr(line, "bne,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "jsr ,") != 0||strstr(line, "jsr,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "red ,") != 0||strstr(line, "red,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "prn ,") != 0||strstr(line, "prn,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "rst ,") != 0||strstr(line, "rst,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "stop ,") != 0||strstr(line, "stop,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function\n",numLine);
                    boolean = 0;
                } 
            }
            numLine++;
        }
    fclose(fp);
    return boolean;
}
int funcArguments(char nameFile[30])
{
    FILE *fp;
    char line[80];
    int psikCount = 0;
    int LineCounter = 1;
    int boolean = 1;
    int i;
    fp = fopen(nameFile,"r"); 
    while ( fgets(line,80,fp) != NULL)
        {
            psikCount = 0;
            for (i = 0; line[i] !='\n'; i++)
            {
                if (line[i] == ',')
                {
                    psikCount++;
                }
                
            }
            if(strstr(line, "mov") != 0  || strstr(line, "cmp") != 0||strstr(line, "add") != 0 
             || strstr(line, "sub") != 0  ||strstr(line, "lea") != 0  )
            {   
                if (psikCount!=1)
                    {
                        printf("eror in line %d: function have to get 2 arguments\n",LineCounter);
                        boolean = 0;
                    }
                    
            }
            else if(strstr(line, "clr") != 0  || strstr(line, "not") != 0||strstr(line, "jmp") != 0 
             || strstr(line, "inc") != 0  ||strstr(line, "dec") != 0||strstr(line, "jsr")!= 0
             || strstr(line, "jmp") != 0  ||strstr(line, "bne") != 0 ||strstr(line, "red")!= 0
             ||strstr(line, "prn" ))
            {   
                if (psikCount != 0 )
                    {
                        printf("eror in line %d: function can not have more then one arguments\n",LineCounter);
                        boolean = 0;
                    }
            }
            else if (strstr(line, "rst") != 0  ||strstr(line, "stop") != 0  )
            {
                if (strstr(line, ","))
                    {
                        printf("eror in line %d: function can not have arguments\n",LineCounter);
                        boolean = 0;
                    }
            }
            LineCounter++;
        }
        fclose(fp);
    return boolean;
}