#include <stdio.h>
#include <string.h>
char fileName[20] = "bar2.txt";
int checkFile(FILE *fp);
int checkDot(int boolean,FILE *fp);
int checkColon(int boolean,FILE *fp);
int checkEntExt(int boolean,FILE *fp);
int firstWord(int boolean,FILE *fp);
int checkFirstWord(int boolean,FILE *fp);
int checkExtEntrLable(int boolean,FILE *fp);
// void main()
// {
//     FILE *fp;
//     fp = fopen(fileName,"r"); 
//     //checkExtEntrLable(1,fp);
//     //printf("bla blab bala",checkEntExt(1,fp));
//     fclose(fp);
// }
int erorFile(FILE *fp)
{
    int boolean = 1;
    if (!checkFile(fp))
    {    /*open file with not exists file*/
        boolean = 0;
    }
    if (sizeLineCheck(fp)>80)
    {    /*open file with not exists file*/
        boolean = 0;
    }
    if (!checkDot(1,fp))
    {    /*open file DOTE not use well*/
        boolean = 0;
    }
    if (!checkColon(1,fp))
    {    /*open file DOTE not use well*/
        boolean = 0;
    }
    if (!checkfunc(1,fp))
    {    /*open file DOTE not use well*/
        boolean = 0;
    }
    if (!checkHash(1,fp))
    {    /*open file DOTE not use well*/
        boolean = 0;
    }
    
}
int checkfunc(int boolean, FILE *fp)//check if all function write with lower case
{   

    char line[80];
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, "MOV") != 0)
            {
                boolean = 0;
            }  
            if(strstr(line, "CMP") != 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "ADD")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "SUB")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "LEA")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "CLR")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "NOT")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "INC")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "DEC")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "JMP")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "BNE")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "JSR")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "RED")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "PRN")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "RTS")!= 0)
            {
                boolean = 0;
            } 
            if(strstr(line, "STOP")!= 0)
            {
                boolean = 0;
            } 
        }
    return boolean;

}
int checkHash(int boolean,FILE *fp)//check no space after " # "
{
    char line[80];
    int numLine = 1;
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, "# ") != 0)
            {
                printf("eror in line %d: hash not use corectly",numLine);
                boolean = 0;
            }  
            numLine++;
        }
    return boolean;
}
int checkFile(FILE *fp)//check if file exist
{
    if(fp == NULL)
    {
        printf(" File does not exist or can not be opened.\n"); 
        return 0;
    }
    return 1;
}
int checkDot(int boolean,FILE *fp)//check if after dot there is no space and right name
{
    char line[80];
    int numLine = 1;
    while ( fgets(line,80,fp) != NULL)
        {
            if(strstr(line, ". ") != 0||strstr(line, ".\n") != 0)
            {
                printf("eror in line %d: DOT with space after it",numLine);
                boolean =0 ;
            }  
            if(strstr(line, ".") != 0&&(strstr(line, ".data") == 0||strstr(line, ".string") == 0|| strstr(line, ".entry") == 0||strstr(line, ".extern") == 0))
            {
                printf("eror in line %d: use dot without any rigth functions",numLine);
                boolean = 0;
            }  
            numLine++;
        }
        return boolean;
}
int checkColon(int boolean,FILE *fp)//check that there is no space before " : "
{
    char line[80];
    int numLine = 1;
    while ( fgets(line,80,fp) != NULL)
        {
            if( strstr(line, " :") != 0  || (strstr(line, ":") != 0 && strstr(line, ": ") == 0)) 
            {
                printf("eror in line %d: ':' not use right",numLine);
                boolean = 0;
            }
            numLine++;
        }
    return boolean;
}
int sizeLineCheck(FILE *fp )//check if there is line bigger then 80
{
    char str[100],longest[100];
    int len = 0;

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
         printf("eror in line : the file include lines longer then 80");
         return 0;
     }
     
    return 1;
}
int checkStrDat(int boolean,FILE *fp)//check if string or data write well
{
    char line[80];
    int numLine = 1;
    while ( fgets(line,80,fp) != NULL)
        {
            if( (strstr(line, ".string") != 0&&strstr(line, ".string ") == 0) || (strstr(line, ".data ") != 0 &&strstr(line, ".data ") == 0) ) 
            {
                printf("eror in line %d: .string or .data write without space after it",numLine);
                boolean = 0;
            }
            if( strstr(line, ".STRING") != 0  || strstr(line, ".DATA") != 0 ) 
            {
                printf("eror in line %d: .string or .data write in Capital letters",numLine);
                boolean = 0;
            }
            numLine++;
        }
    return boolean;
}
int checkEntExt(int boolean,FILE *fp)//check if entry and extern first in line**********check if its right
{
    char line[80];
    while ( fgets(line,80,fp) != NULL)
        {
            if( strstr(line, "extern") != 0  || strstr(line, "entry") != 0 ) 
            {   
                if(strstr(line, "\n.extern") == 0  || strstr(line, "\n.entry") == 0)
                boolean = 0;
            }
        }
    return boolean;
}
int checkFirstWord(int boolean,FILE *fp)
{
    char word[30];
    int numLine = 1;
    while (!feof(fp))
    {
        fscanf(fp,"%s%*[^\n]",word);
         if(strcmp(word,".string") == 0|| strcmp(word,".data") == 0)
            {
                printf("eror in line %d: .string or .data is the first ward\n",numLine);
                boolean = 0;
            }
        numLine++;
    }
    return boolean;
}
int checkExtEntrLable(int boolean,FILE *fp)
{
    char word[30];
    char wordArray[30][30];
    int getIn = 0;
    int i = 0;
    int j;
    int numLine = 0;
    while (!feof(fp))
    {
        fscanf(fp,"%s*[^\n]",word);
        if(strcmp(word,".entry") == 0|| strcmp(word,".extern") == 0)
            {
                getIn = 1;
                fscanf(fp,"%s*[^\n]",word);
            }
        if (getIn == 1)
        {
            getIn = 0 ;
            for(j = 0; j < 30; ++j)
            {
                if(strcmp(wordArray[j], word) == 0)
                {
                    printf("eror in line %d: Lable cant be use twise\n",numLine);
                    boolean = 0;

                }
            }
            if (boolean == 1)
            {
                for(j = 0; j<30;j++)
                {
                      wordArray[i][j]= word[j];
                }
                i++;
            }
        }  
        numLine++;
    }
    return boolean;
}
int checkComma(int boolean,FILE *fp)
{
    char line[80];
    int numLine = 1;
    while ( fgets(line,80,fp) != NULL)
        {
            if( strstr(line, ",\n") != 0 ) 
            {   
                printf("eror in line %d: con't be ',' at the end of line",numLine);
                boolean = 0;
            }
            else 
            {
                if(strstr(line, "mov ,") != 0||strstr(line, "mov,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                }  
                if(strstr(line, "cmp ,") != 0||strstr(line, "cmp,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "add ,") != 0||strstr(line, "add,") != 0)
                {
                    printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "sub ,") != 0||strstr(line, "sub,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "lea ,") != 0||strstr(line, "lea,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "clr ,") != 0||strstr(line, "clr,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "not ,") != 0||strstr(line, "not,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "inc ,") != 0||strstr(line, "inc,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "dec ,") != 0||strstr(line, "dec,") != 0)
                {
                    boolean = 0;
                } 
                if(strstr(line, "jmp ,") != 0||strstr(line, "jmp,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "bne ,") != 0||strstr(line, "bne,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "jsr ,") != 0||strstr(line, "jsr,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "red ,") != 0||strstr(line, "red,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "prn ,") != 0||strstr(line, "prn,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "rst ,") != 0||strstr(line, "rst,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
                if(strstr(line, "stop ,") != 0||strstr(line, "stop,") != 0)
                {
                     printf("eror in line %d: con't be ',' after function",numLine);
                    boolean = 0;
                } 
            }
            numLine++;
        }
    return boolean;
}
// int funcArguments(int boolean,FILE *fp)
// {
//     char line[80];
//     int numArgument = 3;
//     int LineCounter = 1;
//     while ( fgets(line,80,fp) != NULL)
//         {
//             if(strstr(line, "mov") != 0  || strstr(line, "cmp") != 0||strstr(line, "add") != 0 
//              || strstr(line, "sub") != 0  ||strstr(line, "lea") != 0  )
//             {   
//                 numArgument = 2;
//             }
//             if(strstr(line, "clr") != 0  || strstr(line, "not") != 0||strstr(line, "jmp") != 0 
//              || strstr(line, "inc") != 0  ||strstr(line, "dec") != 0||strstr(line, "jsr")!= 0
//              || strstr(line, "jmp") != 0  ||strstr(line, "bne") != 0 ||strstr(line, "red")!= 0
//              ||strstr(line, "prn" ))
//             {   
//                 numArgument = 1;
//             }
//             if (strstr(line, "rst") != 0  ||strstr(line, "stop") != 0  )
//             {
//                 numArgument = 0;
//             }
//             switch (numArgument)
//             {
//             case 0:
//                     if (strstr(line, ",") != 0)
//                     {
//                         printf("eror in line %d: function can not have arguments",LineCounter);
//                         boolean = 0;
//                     }
                    
//                 break;
//             case 1:
//                 if (strstr(line, ",") != 0)
//                     {
//                         printf("eror in line %d: function can not have more then one arguments",LineCounter);
//                         boolean = 0;
//                     }
//                 break;
//             case 2:
//                     if (strstr(line, ",") == 0)
//                     {
//                         printf("eror in line %d: function have to get 2 arguments",LineCounter);
//                         boolean = 0;
//                     }
//             break;
//             default:
//                 break;
//             }
//         }
//     return boolean;
// }