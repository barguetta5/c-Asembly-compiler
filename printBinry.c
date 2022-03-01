#include <stdio.h>
#include <stdlib.h>
#include "simbalTable2.c"

void codeToBinary(char *line,char *ptr);
int recognizeOperands(char *array);
int wichOger(char *line,int *binaryArray);
int wichOgerMacor(char *line,int *binaryArray);
int wichOgerYaad(char *line,int *binaryArray);
void initializ(int binaryArray[20]);
void initializTab(int binaryArray[20]);
void initializNegativ(int binaryArray[20]);
void intToBinary(char num[3],int binaryArray[20]);
void intToBinary2(char *line,int num,int binaryArray[20]);
void numberPrint(char *line,int *binaryArray);
int baseLabe(char *line);
int offsetLabe(char *line);
int twoOperands(char *line,int *binaryArray);
void insertToFile(FILE *fptr,int *binaryArray,int counterIc);
void main()
{
    int i;
    char *line = (char*)malloc(80*sizeof(char));
    char *ptr;
    ptr   = fileToArray();
    // for (i = 0; i < simbCount; i++)
    // {
    //     printTable(tab[i]);
    // }
    //printf("%s",ptr);
    codeToBinary(line,ptr);
    //fclose(binaryFile);
}
void codeToBinary(char *line,char *ptr)
{
    FILE *binaryFile;
    int binaryArray[20];
    int funcType;
    char firstFunc[5][3] = {"mov","cmp","add","sub","lea"};
    char fiveFunc[4][3] = {"clr","nor","inc","dec"};
    char nineFunc[4][3] = {"jmp","bne","jsr"};
    int i = 0;
    int indexLine = 0;
    int counterIc = 100;
    binaryFile = fopen("binaryFile.txt", "w");
    initializ(binaryArray);
    while (i<sz)
    {
        memset(line,'\0',80*sizeof(char));
        
        indexLine = 0;
        while (ptr[i]!='\n'&&i<sz)
        {
            line[indexLine] = ptr[i];
            i++;
            indexLine++;
        }
        i++;
        funcType =  recognizeOperands(line);

        switch (funcType)
        {
            case 0:
                    if (strstr(line,".extern"))
                    {
                        counterIc = 100;
                    } 
                break;
            case 1:
                    if (strstr(line,"red"))
                    {
                        binaryArray[18] = 1;
                        binaryArray[12] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                    else if (strstr(line,"prn"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[13] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                    if (strstr(line,"#"))
                    {
                        binaryArray[18] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        numberPrint(line,binaryArray);
                        binaryArray[18] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                    else if (checkOgerInArray(line) == 1 && !strstr(line,"["))
                    {
                        binaryArray[18] = 1;
                        wichOger(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                    else
                    {
                        binaryArray[18] = 1;
                        binaryArray[0] = 1;;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[17] = 1;
                        intToBinary2(baseLabe(line),binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[17] = 1;
                        intToBinary2(offsetLabe(line),binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                break;
            case 2:
                    if (strstr(line,"mov"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[0] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        twoOperands(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        if (strstr(line,"mov #"))
                        {
                            numberPrint(line,binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
        
                        }
                        else if(strstr(line,"mov r"))
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        
                        
                    }
                    else if (strstr(line,"cmp"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[1] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        twoOperands(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        if (strstr(line,"cmp #"))
                        {
                            numberPrint(line,binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
        
                        }
                        else if(strstr(line,"cmp r"))
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                    }
                    else if (strstr(line,"add"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[2] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[18] = 1;//print first line
                        binaryArray[15] = 1;
                        binaryArray[13] = 1;
                        twoOperands(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        if (strstr(line,"add #"))
                        {
                            numberPrint(line,binaryArray);
                            /*insert to file*/
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                /*insert to file*/
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                /*insert to file*/
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                /*insert to file*/
                                initializ(binaryArray);
                                counterIc++;
                            }
        
                        }
                        else if(strstr(line,"add r"))
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                printf("%d\nabbbbbb\n",counterIc);
                                intToBinary2(line,baseLabe(line),binaryArray);
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    printf("got in2\n");
                                    binaryArray[17] = 1;
                                }
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }

                    }
                    else if (strstr(line,"sub"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[3] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[18] = 1;//print first line
                        binaryArray[15] = 1;
                        binaryArray[13] = 1;
                        binaryArray[12] = 1;
                        twoOperands(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        if (strstr(line,"sub #"))
                        {
                            numberPrint(line,binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
        
                        }
                        else if(strstr(line,"sub r"))
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }

                    }
                    else if (strstr(line,"lea"))
                    {
                        binaryArray[18] = 1;//print first line
                        binaryArray[4] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        twoOperands(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        if (strstr(line,"lea #"))
                        {
                            numberPrint(line,binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
        
                        }
                        else if(strstr(line,"lea r"))
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (baseLabe(line) == 0)
                            {
                                binaryArray[16] = 1;
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                if (baseLabe(line) == 0)
                                {
                                    binaryArray[16] = 1;
                                }
                                else
                                {
                                    binaryArray[17] = 1;
                                }
                                intToBinary2(offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                    }
                    printf("here");
                break;
            case 3:
                    if (strstr(line,"stop"))
                    {
                        binaryArray[18] = 1;
                        binaryArray[15] = 1;
                    }
                    else
                    {
                        binaryArray[18] = 1;
                        binaryArray[14] = 1;
                    }
                    insertToFile(binaryFile,binaryArray,counterIc);
                    initializ(binaryArray);
                    counterIc++;
                break;    
            default:
                break;
        }  
    }
}
int recognizeOperands(char *array)
{
    if (strstr(array,".extern")||strstr(array,".entry"))
    {
        return 0;
    }
    else if (strstr(array,"clr")||strstr(array,"not")||strstr(array,"inc")||strstr(array,"dec")||strstr(array,"jmp")
            ||strstr(array,"bne")||strstr(array,"jsr")||strstr(array,"red")||strstr(array,"prn"))
    {
        return 1;
    }
    else if (strstr(array,"mov")||strstr(array,"cmp")||strstr(array,"add")||strstr(array,"sub")||strstr(array,"lea"))
    {
        return 2;

    }
    else if (strstr(array,"stop")||strstr(array,"rts"))
    {
        return 3;
    }  
    else
    {    
        return 4;
    }
}
int wichOger(char *line,int *binaryArray)
{
    binaryArray[0] = 1;
    binaryArray[1] = 1;
    if (strstr(line,"r0"))
    {
        return 0;
    }
    else if (strstr(line,"r1"))
    {
        binaryArray[2] = 1;
        return 1;
    }
    else if (strstr(line,"r2"))
    {
        binaryArray[3] = 1;
        return 2;
    }
    else if (strstr(line,"r3"))
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        return 3;
    }
    else if (strstr(line,"r4"))
    {
        binaryArray[4] = 1;
        return 4;
    }
    else if (strstr(line,"r5"))
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        return 5;
    }
    else if (strstr(line,"r6"))
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 6;
    }
    else if (strstr(line,"r7"))
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 7;
    }
    else if (strstr(line,"r8"))
    {
        binaryArray[5] = 1;
        return 8;
    }
    else if (strstr(line,"r9"))
    {
        binaryArray[2] = 1;
        binaryArray[5] = 1;
        return 9;
    }
    else if (strstr(line,"r10"))
    {
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 10;
    }
    else if (strstr(line,"r11"))
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 11;
    }
    else if (strstr(line,"r12"))
    {
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 12;
    }
    else if (strstr(line,"r13"))
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 13;
    }
    else if (strstr(line,"r14"))
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 14;
    }
    else
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 15;
    }
    
}
int wichOgerMacor(char *line,int *binaryArray)
{
    binaryArray[6] = 1;
    binaryArray[7] = 1;
    int i = 0;
    while (line[i] != 'r')
    {
        i++;
    }
    i++;
    if (line[i] == '0')
    {
        return 0;
    }
    else if (line[i] == '1')
    {
        binaryArray[i] = 1;
        return 1;
    }
    else if (line[i] == '2')
    {
        binaryArray[9] = 1;
        return 2;
    }
    else if (line[i] == '3')
    {
        binaryArray[8] = 1;
        binaryArray[9] = 1;
        return 3;
    }
    else if (line[i] == '4')
    {
        binaryArray[10] = 1;
        return 4;
    }
    else if (line[i] == '5')
    {
        binaryArray[8] = 1;
        binaryArray[10] = 1;
        return 5;
    }
    else if (line[i] == '6')
    {
        binaryArray[9] = 1;
        binaryArray[10] = 1;
        return 6;
    }
    else if (line[i] == '7')
    {
        binaryArray[8] = 1;
        binaryArray[9] = 1;
        binaryArray[10] = 1;
        return 7;
    }
    else if (line[i] == '8')
    {
        binaryArray[11] = 1;
        return 8;
    }
    else if (line[i] == '9')
    {
        binaryArray[8] = 1;
        binaryArray[11] = 1;
        return 9;
    }
    else if (line[i] == '1' && line[i+1] == '0')
    {
        binaryArray[9] = 1;
        binaryArray[11] = 1;
        return 10;
    }
    else if (line[i] == '1'&& line[i+1] == '1')
    {
        binaryArray[8] = 1;
        binaryArray[9] = 1;
        binaryArray[11] = 1;
        return 11;
    }
    else if (line[i]  == '1'&& line[i+1] == '2')
    {
        binaryArray[10] = 1;
        binaryArray[11] = 1;
        return 12;
    }
    else if (line[i]  == '1'&& line[i+1] == '3')
    {
        binaryArray[8] = 1;
        binaryArray[10] = 1;
        binaryArray[11] = 1;
        return 13;
    }
    else if (line[i]  == '1' && line[i+1] == '4')
    {
        binaryArray[9] = 1;
        binaryArray[10] = 1;
        binaryArray[11] = 1;
        return 14;
    }
    else
    {
        binaryArray[8] = 1;
        binaryArray[9] = 1;
        binaryArray[10] = 1;
        binaryArray[11] = 1;
        return 15;
    }
    
}
int wichOgerYaad(char *line,int *binaryArray)
{
    binaryArray[0] = 1;
    binaryArray[1] = 1;
    if (line[6] == '0')
    {
        return 0;
    }
    else if (line[6] == '1')
    {
        binaryArray[2] = 1;
        return 1;
    }
    else if (line[6] == '2')
    {
        binaryArray[3] = 1;
        return 2;
    }
    else if (line[6] == '3')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        return 3;
    }
    else if (line[6] == '4')
    {
        binaryArray[4] = 1;
        return 4;
    }
    else if (line[6] == '5')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        return 5;
    }
    else if (line[6] == '6')
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 6;
    }
    else if (line[6] == '7')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 7;
    }
    else if (line[6] == '8')
    {
        binaryArray[5] = 1;
        return 8;
    }
    else if (line[6] == '9')
    {
        binaryArray[2] = 1;
        binaryArray[5] = 1;
        return 9;
    }
    else if (line[6] == '1' && line[7] == '0')
    {
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 10;
    }
    else if (line[6] == '1'&& line[7] == '1')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 11;
    }
    else if (line[6] == '1'&& line[7] == '2')
    {
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 12;
    }
    else if (line[6] == '1'&& line[7] == '3')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 13;
    }
    else if (line[6] == '1' && line[7] == '4')
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 14;
    }
    else
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 15;
    }
}
void initializ(int binaryArray[20])
{
    for(int i = 0;i<20;i++)
    {
        binaryArray[i] = 0;
    }
}
void initializTab(int binaryArray[20])
{
    for(int i = 0;i<20;i++)
    {
        binaryArray[i] = 0;
    }
    binaryArray[17] = 1;
}
void initializNegativ(int binaryArray[20])
{
    for(int i = 0;i<17;i++)
    {
        binaryArray[i] = 1;
    }
    binaryArray[19] = 0;
    binaryArray[18] = 0;
    binaryArray[17] = 0;
    binaryArray[16] = 0;
}
void intToBinary(char num[3],int binaryArray[20])
{
    int number;
    int i = 0;
    int negative = 0;
    int even = 0;
    number = atoi(num);
    initializ(binaryArray);
    if (number<0)
    {
        negative = 1;
        number = number*(-1);
        number--;
        initializNegativ(binaryArray);
    }
    while (number>0)
    {
        if (negative && number%2 == 1) 
        {
            binaryArray[i] = 0;
        }
        else if (!negative && number%2 == 1)
        {
            binaryArray[i] = number%2;
        }
        i++;
        number = number / 2;
    }
}
void intToBinary2(char *line,int num,int binaryArray[20])
{
    int i = 0;
    int negative = 0;
    int even = 0;
    initializ(binaryArray);
    if (num<0)
    {
        negative = 1;
        num = num*(-1);
        num--;
        initializNegativ(binaryArray);
    }
    while (num>0)
    {
        if (negative && num%2 == 1) 
        {
            binaryArray[i] = 0;
        }
        else if (!negative && num%2 == 1)
        {
            binaryArray[i] = num%2;
        }
        i++;
        num = num / 2;
    }
    if (baseLabe(line) == 0)
        {
            binaryArray[16] = 1;
        }
        else
        {
            printf("got in2\n");
            binaryArray[17] = 1;
        }
    
}
void numberPrint(char *line,int *binaryArray)//aske for line and return binary number in line
{
    int i = 0 ;
    int j = 0;
    char *num;
    num = (char*)malloc(5);
    while (line[i] != '#')
    {
        i++;
    }
    i++;
    while (line[i] != ' ')
    {
        num[j] = line[i];
        j++;
        i++;
    }
    intToBinary(num,binaryArray);
    free(num);
}
int baseLabe(char *line)// return the base of the lable
{
    int i = 0;
    while (!strstr(line,tab[i].lab))
    {
        i++;
    }
    return tab[i].base;
}
int offsetLabe(char *line)// return the offset of the lable
{
    int i = 0;
    while (!strstr(line,tab[i].lab))
    {
        i++;
    }
    return tab[i].offset;
}
int twoOperands(char *line,int *binaryArray)//check wich miun is it
{
    int i = 0;
    if (strstr(line,"v #")||strstr(line,"d #")||strstr(line,"p #")||strstr(line,"b #")||strstr(line,"a #"))
    {
        if (strstr(line,", r"))
        {
            wichOgerYaad(line,binaryArray);
            return 1 ;
        }
        else if (strstr(line,", #"))
        {
            return 2;
        }
        else
        {
            binaryArray[0] = 1;
            return 5;
        }

    }
    else if(strstr(line,"v r")||strstr(line,"d r")||strstr(line,"p r")||strstr(line,"b r")||strstr(line,"a r"))
    {
        wichOgerMacor(line,binaryArray);
        if (strstr(line,", r"))
        {
            wichOgerYaad(line,binaryArray);
            return 0 ;
        }
        else if (strstr(line,", #"))
        {
            return 1;
        }
        else
        {
            binaryArray[0] = 1;
            return 2;
        } 
    }
    else
    {
    // while (!strstr(line,tab[i].lab))
    // {
    //     i++;
    // }
        binaryArray[6] = 1;
         if (strstr(line,", r"))
        {
            wichOgerYaad(line,binaryArray);
            return 2 ;
        }
        else if (strstr(line,", #"))
        {
            return 5;
        }
        else
        {
            binaryArray[0] = 1;
            return 6;
        } 
    }
    

    
}
void insertToFile(FILE *fptr,int *binaryArray,int counterIc) //this method print to file the binary table 
{
  
    fprintf(fptr,"%d %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",counterIc,binaryArray[19],binaryArray[18]
    ,binaryArray[17],binaryArray[16],binaryArray[15],binaryArray[14],binaryArray[13],binaryArray[12],binaryArray[11]
    ,binaryArray[10],binaryArray[9],binaryArray[8],binaryArray[7],binaryArray[6],binaryArray[5]
    ,binaryArray[4],binaryArray[3],binaryArray[2],binaryArray[1],binaryArray[0]);
}