#include <stdio.h>
#include <stdlib.h>
#include "simbalTable2.c"

#define binarryArraySize 20
#define sizeName 30
#define sizeLines 80

void printBinToChar(char character,int *binaryArray);
int codeToBinary(char *line,char *ptr);
int recognizeOperands(char *array);
int wichOger(char *line,int *binaryArray);
int wichOgerMacor(char *line,int *binaryArray);
int wichOgerYaad(char *line,int *binaryArray);
void initializ(int binaryArray[binarryArraySize]);
void initializNegativ(int binaryArray[binarryArraySize]);
void intToBinary(char num[5],int binaryArray[binarryArraySize]);
void intToBinary2(char *line,int num,int binaryArray[binarryArraySize]);
void numberPrint(char *line,int *binaryArray);
int baseLabe(char *line);
int offsetLabe(char *line);
int twoOperands(char *line,int *binaryArray);
int insertToFile(FILE *fptr,int *binaryArray,int counterIc);
int checkOgerInArray(char array[sizeLines]);
void oneOperandFunc(char *line,int *binaryArray);
int wichOgerInLab(char *line,int *binaryArray);
int wichOgerInLabM(char *line,int *binaryArray);
int startBinaryPrint(char newNameFile[sizeName]);
int insertToPsFile(FILE *fptr,char lableName[sizeName],int counterIc);
char *nameLabele(char *line);
int baseLabe(char *line);
void numberRes(char *line,int *binaryArray);
void entryFile();


int startBinaryPrint(char newNameFile[sizeName])
{
    int i;
    char *line = (char*)malloc(80*sizeof(char));
    char *ptr;
    int number;
    ptr   = fileToArray(newNameFile);
    for (i = 0; i < simbCount; i++)
    {
        printTable(tab[i]);
    }
    number = codeToBinary(line,ptr);
    entryFile();
    free(line);
    free(ptr);
    return number;
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
int codeToBinary(char *line,char *ptr)
{
    FILE *binaryFile;
    FILE * psF;
    int binaryArray[binarryArraySize];
    char *num;
    int numIndex;
    int funcType;
    int i = 0;
    int j;
    int numberNotFu = 0;
    int indexLine = 0;
    int counterIc = 100;
    binaryFile = fopen("binaryFile.txt", "w");
    psF = fopen("ps.ext", "w");
    num = (char*)malloc(5);
    initializ(binaryArray);//initialized the array to zeroes
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
                    else
                    {
                       
                        binaryArray[18] = 1;
                        if (strstr(line,"clr")||strstr(line,"not")||strstr(line,"inc")
                          ||strstr(line,"dec"))
                        {
                             
                            binaryArray[5] = 1;
                        }
                        else if(strstr(line,"jmp")||strstr(line,"bne")||strstr(line,"jsr"))
                        {
                            binaryArray[9] = 1;
                        }
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
                        oneOperandFunc(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                    }
                    else
                    {
                        binaryArray[18] = 1;
                        binaryArray[0] = 1;
                        if (strstr(line,"["))
                        {
                            wichOgerInLab(line,binaryArray);
                        }
                        oneOperandFunc(line,binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[17] = 1;
                        if (baseLabe(line) == 0)
                        {
                            insertToPsFile(psF,nameLabele(line),counterIc);
                            insertToPsFile(psF,nameLabele(line),counterIc+1);
                        }
                        intToBinary2(line,baseLabe(line),binaryArray);
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[17] = 1;
                        intToBinary2(line,offsetLabe(line),binaryArray);
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
                        binaryArray[18] = 1;
                        twoOperands(line,binaryArray);
                        if (strstr(line,"] ,") ||strstr(line,"],"))
                            {
                                
                                wichOgerInLabM(line,binaryArray);
                            }
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
 
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                insertToPsFile(psF,nameLabele(line),counterIc);
                                insertToPsFile(psF,nameLabele(line),counterIc+1);
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            
                            intToBinary2(line,baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;

                            intToBinary2(line,offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                binaryArray[18] = 1;
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
            
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                        binaryArray[18] = 1;
                        twoOperands(line,binaryArray);
                        if (strstr(line,"] ,") ||strstr(line,"],"))
                            {
                                
                                wichOgerInLabM(line,binaryArray);
                            }
                            
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
                                
                                j = 0;
                                numIndex = 0;
                                
                                while (line[j]!='#')
                                {
                                    j++;
                                }
                                j++;
                                while (line[j]!='\n'&&j<30)
                                {
                                    if (line[j] == '+'||line[j] == '-' )
                                    {
                                        num[numIndex] = line[j];
                                        numIndex++;
                                    }
                                    else if (line[j] == '0' ||line[j] == '1' ||line[j] == '2' 
                                    ||line[j] == '3' ||line[j] == '4' ||line[j] == '5' ||line[j] == '6' 
                                    ||line[j] == '7' ||line[j] == '8' ||line[j] == '9' )
                                    {
                                        num[numIndex] = line[j];
                                        numIndex++;
                                    }
                                }
                                binaryArray[18] = 1;
                                intToBinary(num,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                memset(num,'\0',5);
                                numIndex = 0;

                                // numberPrint(line,binaryArray);
                                // insertToFile(binaryFile,binaryArray,counterIc);
                                // initializ(binaryArray);
                                // counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
     
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }

                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                            intToBinary2(line,baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;

                            intToBinary2(line,offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {

                                numberRes(line,binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                                //memset(num,'\0',5);
                                //numIndex = 0;
                                
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                        if (strstr(line,"] ,") ||strstr(line,"],"))
                            {
                                
                                wichOgerInLabM(line,binaryArray);
                            }
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                /*insert to file*/
                                initializ(binaryArray);
                                counterIc++;
  
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);

                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }

                            intToBinary2(line,baseLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;

                            intToBinary2(line,offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                binaryArray[18] = 1;
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }

                    }
                    else if (strstr(line,"sub"))
                    {
                        
                        binaryArray[18] = 1;//print first line
                        binaryArray[2] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        binaryArray[18] = 1;//print first line
                        binaryArray[15] = 1;
                        binaryArray[13] = 1;
                        binaryArray[12] = 1;
                        twoOperands(line,binaryArray);
                        if (strstr(line,"] ,") ||strstr(line,"],"))
                            {
                                wichOgerInLabM(line,binaryArray);
                            }
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }

                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                        else
                        {
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                binaryArray[18] = 1;
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                        binaryArray[18] = 1;
                        twoOperands(line,binaryArray);
                        if (strstr(line,"] ,") ||strstr(line,"],"))
                            { 
                                wichOgerInLabM(line,binaryArray);
                            }
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
 
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
  
                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }
                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
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
                                insertToPsFile(psF,nameLabele(line),counterIc);
                                insertToPsFile(psF,nameLabele(line),counterIc+1);
                            }
                            else
                            {
                                binaryArray[17] = 1;
                            }
                            intToBinary2(line,baseLabe(line),binaryArray);
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
                            intToBinary2(line,offsetLabe(line),binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            if (strstr(line,", r"))
                            {}
                            else if (strstr(line,", #"))
                            {
                                numberPrint(line,binaryArray);
                                binaryArray[18] = 1;
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                            else
                            {
                                if (baseLabe(line) == 0)
                                {
                                    insertToPsFile(psF,nameLabele(line),counterIc);
                                    insertToPsFile(psF,nameLabele(line),counterIc+1);
                                }

                                intToBinary2(line,baseLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;

                                intToBinary2(line,offsetLabe(line),binaryArray);
                                insertToFile(binaryFile,binaryArray,counterIc);
                                initializ(binaryArray);
                                counterIc++;
                            }
                        }
                    }
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
                    if (strstr(line,".string"))
                    {
                        j = 0;
                        while (line[j]!= '.')
                        {
                            j++;
                        }
                        j+=9;
                        while (line[j] !='"')
                        {
                            
                            printBinToChar(line[j],binaryArray);
                            binaryArray[18] = 1;
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            numberNotFu++;
                            j++;

                        }
                        binaryArray[18] = 1;
                        insertToFile(binaryFile,binaryArray,counterIc);
                        initializ(binaryArray);
                        counterIc++;
                        numberNotFu++;

                    }
                    else if (strstr(line,".data"))
                    {
                        binaryArray[18] = 1;
                        if (!strstr(line,","))
                        {
                            j = 0;
                            numIndex = 0;
                            while (line[j]!='\n' && j<30)
                            {
                                if (line[j] == '+'||line[j] == '-' )
                                {
                                    num[numIndex] = line[j];
                                    numIndex++;
                                }
                                else if (line[j] == '0' ||line[j] == '1' ||line[j] == '2' ||line[j] == '3' ||line[j] == '4' 
                                ||line[j] == '5' ||line[j] == '6' ||line[j] == '7' ||line[j] == '8' ||line[j] == '9' )
                                {
                                    num[numIndex] = line[j];
                                    numIndex++;    
                                }                           
                                j++;
                            }
                            binaryArray[18] = 1;
                            intToBinary(num,binaryArray);
                            insertToFile(binaryFile,binaryArray,counterIc);
                            initializ(binaryArray);
                            counterIc++;
                            numberNotFu++;
                            memset(num,'\0',5);
                            
                        }
                        else
                        {
                            j = 0;
                            numIndex = 0;
                            memset(num,'\0',5);
                            while (line[j]!='\n' && j<strlen(line))
                            {
                                if (line[j] == '+'||line[j] == '-' )
                                {
                                    num[numIndex] = line[j];
                                    numIndex++;
                                }
                                else if (line[j] == '0' ||line[j] == '1' ||line[j] == '2' ||line[j] == '3' ||line[j] == '4' 
                                ||line[j] == '5' ||line[j] == '6' ||line[j] == '7' ||line[j] == '8' ||line[j] == '9' )
                                {
                                    num[numIndex] = line[j];
                                    numIndex++;
                                }
                                if (line[j] == ',' || j == strlen(line)-1)
                                {
                                    binaryArray[18] = 1;
                                    intToBinary(num,binaryArray);
                                    insertToFile(binaryFile,binaryArray,counterIc);
                                    initializ(binaryArray);
                                    counterIc++;
                                    numberNotFu++;
                                    memset(num,'\0',5);
                                    numIndex = 0;
                                }
                                
                                j++;
                            }
                            
                        }
                    }
                break;
        }  
    }
    free(num);
    fclose(binaryFile);
    fclose(psF);
    return numberNotFu;
}
void printBinToChar(char character,int *binaryArray)
{
    char output[20];
    int i ;
    itoa(character, output, 2);
    strrev(output);
    for (i = 0; i <20; i++)
    {
        if (output[i] == '1')
        {
            binaryArray[i] = 1;
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
    else if (line[i] == '1' && line[i+1] != '0'&&line[i+1] != '1'&&line[i+1] != '2'&&line[i+1] != '3'
    &&line[i+1] != '4'&&line[i+1] != '5')
    {
        binaryArray[2] = 1;
        return 1;
    }
    else if (line[i] == '2')
    {
        binaryArray[3] = 1;
        return 2;
    }
    else if (line[i] == '3')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        return 3;
    }
    else if (line[i] == '4')
    {
        binaryArray[4] = 1;
        return 4;
    }
    else if (line[i] == '5')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        return 5;
    }
    else if (line[i] == '6')
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 6;
    }
    else if (line[i] == '7')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 7;
    }
    else if (line[i] == '8')
    {
        binaryArray[5] = 1;
        return 8;
    }
    else if (line[i] == '9')
    {
        binaryArray[2] = 1;
        binaryArray[5] = 1;
        return 9;
    }
    else if (line[i] == '1' && line[i+1] == '0')
    {
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 10;
    }
    else if (line[i]  == '1'&& line[i+1]  == '1')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 11;
    }
    else if (line[i]  == '1'&& line[i+1]  == '2')
    {
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 12;
    }
    else if (line[i] == '1'&& line[i+1]  == '3')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 13;
    }
    else if (line[i] == '1' && line[i+1]  == '4')
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
    else if (line[i] == '1' && line[i+1] != '0'&&line[i+1] != '1'&&line[i+1] != '2'&&line[i+1] != '3'
    &&line[i+1] != '4'&&line[i+1] != '5')
    {
        binaryArray[8] = 1;
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
    int i = 0;
    while (line[i] != ',')
    {
        i++;
    }
    while (line[i] != 'r')
    {
        i++;
    }
    i++;
    if (line[i] == '0')
    {
        return 0;
    }
    else if (line[i] == '1' && line[i+1] != '0'&&line[i+1] != '1'&&line[i+1] != '2'&&line[i+1] != '3'
    &&line[i+1] != '4'&&line[i+1] != '5')
    {
        binaryArray[2] = 1;
        return 1;
    }
    else if (line[i] == '2')
    {
        binaryArray[3] = 1;
        return 2;
    }
    else if (line[i] == '3')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        return 3;
    }
    else if (line[i] == '4')
    {
        binaryArray[4] = 1;
        return 4;
    }
    else if (line[i] == '5')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        return 5;
    }
    else if (line[i] == '6')
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 6;
    }
    else if (line[i] == '7')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 7;
    }
    else if (line[i] == '8')
    {
        binaryArray[5] = 1;
        return 8;
    }
    else if (line[i] == '9')
    {
        binaryArray[2] = 1;
        binaryArray[5] = 1;
        return 9;
    }
    else if (line[i] == '1' && line[i+1] == '0')
    {
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 10;
    }
    else if (line[i]  == '1'&& line[i+1]  == '1')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 11;
    }
    else if (line[i]  == '1'&& line[i+1]  == '2')
    {
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 12;
    }
    else if (line[i] == '1'&& line[i+1]  == '3')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 13;
    }
    else if (line[i] == '1' && line[i+1]  == '4')
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
int wichOgerInLabM(char *line,int *binaryArray)
{
    binaryArray[6] = 0;
    binaryArray[7] = 1;
    int i = 0;
    while (line[i] != '[')
    {
        i++;
    }
    while (line[i] != 'r')
    {
        i++;
    }
    i++;
    if (line[i] == '0')
    {
        return 0;
    }
    else if (line[i] == '1' && line[i+1] != '0'&&line[i+1] != '1'&&line[i+1] != '2'&&line[i+1] != '3'
    &&line[i+1] != '4'&&line[i+1] != '5')
    {
        binaryArray[8] = 1;
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
int wichOgerInLab(char *line,int *binaryArray)
{
    binaryArray[0] = 0;
    binaryArray[1] = 1;
    int i = 0;
    while (line[i] != '[')
    {
        i++;
    }
    while (line[i] != 'r')
    {
        i++;
    }
    i++;
    if (line[i] == '0')
    {
        return 0;
    }
    else if (line[i] == '1' && line[i+1] != '0'&&line[i+1] != '1'&&line[i+1] != '2'&&line[i+1] != '3'
    &&line[i+1] != '4'&&line[i+1] != '5')
    {
        binaryArray[2] = 1;
        return 1;
    }
    else if (line[i] == '2')
    {
        binaryArray[3] = 1;
        return 2;
    }
    else if (line[i] == '3')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        return 3;
    }
    else if (line[i] == '4')
    {
        binaryArray[4] = 1;
        return 4;
    }
    else if (line[i] == '5')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        return 5;
    }
    else if (line[i] == '6')
    {
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 6;
    }
    else if (line[i] == '7')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[4] = 1;
        return 7;
    }
    else if (line[i] == '8')
    {
        binaryArray[5] = 1;
        return 8;
    }
    else if (line[i] == '9')
    {
        binaryArray[2] = 1;
        binaryArray[5] = 1;
        return 9;
    }
    else if (line[i] == '1' && line[i+1] == '0')
    {
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 10;
    }
    else if (line[i]  == '1'&& line[i+1]  == '1')
    {
        binaryArray[2] = 1;
        binaryArray[3] = 1;
        binaryArray[5] = 1;
        return 11;
    }
    else if (line[i]  == '1'&& line[i+1]  == '2')
    {
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 12;
    }
    else if (line[i] == '1'&& line[i+1]  == '3')
    {
        binaryArray[2] = 1;
        binaryArray[4] = 1;
        binaryArray[5] = 1;
        return 13;
    }
    else if (line[i] == '1' && line[i+1]  == '4')
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
void initializ(int binaryArray[binarryArraySize])
{
    for(int i = 0;i<20;i++)
    {
        binaryArray[i] = 0;
    }
}
void initializNegativ(int binaryArray[binarryArraySize])
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
void intToBinary(char num[5],int binaryArray[binarryArraySize])
{
    int number;
    int i = 0;
    int negative = 0;
    int even = 0;
    number = atoi(num);
    initializ(binaryArray);
    binaryArray[18] = 1;
    if (number<0)
    {
        negative = 1;
        number = number*(-1);
        number--;
        initializNegativ(binaryArray);
        binaryArray[18] = 1;
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
void intToBinary2(char *line,int num,int binaryArray[binarryArraySize])
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
            binaryArray[17] = 1;
        }
    
}
void numberPrint(char *line,int *binaryArray)//aske for line and return binary number in line
{
    int i = 0;
    int j = 0;
    char *num1;
    num1 = (char*)malloc(5);
    while (line[i] != '#')
    {
        i++;
    }
    i++;
    while (line[i] != '\n'&&line[i] != ' ')
    {
        num1[j] = line[i];
        j++;
        i++;
    }
    intToBinary(num1,binaryArray);
    free(num1);
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
char *nameLabele(char *line)// return the base of the lable
{
    int i = 0;
    while (!strstr(line,tab[i].lab))
    {
        i++;
    }
    return tab[i].lab;
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
    if (strstr(line,"v #")||strstr(line,"d #")
    ||strstr(line,"p #")||strstr(line,"b #")||strstr(line,"a #"))
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
    else if(strstr(line,"v r")||strstr(line,"d r")
    ||strstr(line,"p r")||strstr(line,"b r")||strstr(line,"a r"))
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
         if (strstr(line,", r")||strstr(line,",r"))
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
int insertToFile(FILE *fptr,int *binaryArray,int counterIc) //this method print to file the binary table 
{    
    fprintf(fptr,"%d %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",counterIc,binaryArray[19],binaryArray[18]
    ,binaryArray[17],binaryArray[16],binaryArray[15],binaryArray[14],binaryArray[13],binaryArray[12],binaryArray[11]
    ,binaryArray[10],binaryArray[9],binaryArray[8],binaryArray[7],binaryArray[6],binaryArray[5]
    ,binaryArray[4],binaryArray[3],binaryArray[2],binaryArray[1],binaryArray[0]);
    return counterIc;
}
int insertToPsFile(FILE *fptr,char lableName[sizeName],int counterIc) //this method print to file the binary table 
{    
    fprintf(fptr,"%s %d \n",lableName,counterIc);
    return counterIc;
}
int checkOgerInArray(char array[sizeLines])//check how much ogrim i have got
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
void numberRes(char *line,int *binaryArray)
    {
        int j = 0 ;
        char num[5];
        int numIndex = 0;
            while (line[j]!='#')
        {
            j++;
        }
        j++;
        while (line[j]!='\n'&&j<30)
        {
            if (line[j] == '+'||line[j] == '-' )
            {
                num[numIndex] = line[j];
                numIndex++;
            }
            else if (line[j] == '0' ||line[j] == '1' ||line[j] == '2' 
            ||line[j] == '3' ||line[j] == '4' ||line[j] == '5' ||line[j] == '6' 
            ||line[j] == '7' ||line[j] == '8' ||line[j] == '9' )
            {
                num[numIndex] = line[j];
                numIndex++;
            }
            j++;
            //printf("%d",j);
        }
        binaryArray[18] = 1;
        intToBinary(num,binaryArray);
    }
void oneOperandFunc(char *line,int *binaryArray)
{ 
    if (strstr(line,"clr"))
    {
        binaryArray[13] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"not"))
    {
        binaryArray[12] = 1;
        binaryArray[13] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"inc"))
    {
        binaryArray[14] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"dec"))
    {
        binaryArray[12] = 1;
        binaryArray[14] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"jmp"))
    {
        binaryArray[13] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"bne"))
    {
        binaryArray[12] = 1;
        binaryArray[13] = 1;
        binaryArray[15] = 1;
    }
    else if (strstr(line,"jsr"))
    {
        binaryArray[14] = 1;
        binaryArray[15] = 1;
        
    }
        
}
