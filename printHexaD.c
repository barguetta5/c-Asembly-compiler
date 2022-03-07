#include <stdio.h>
#include <stdlib.h>

#define lengthLine 81

char numberToHexca(int number);
int binaryConvert(char line[4]);
void insertToFile(FILE *fptr,char hexa[18]);
void getLine();
void insertHexa(char line[lengthLine],FILE *newF);


void getLine()//get line from binary file and convert to hexa decimal
{
    FILE *fptr;
    FILE *newF;
    char line[lengthLine];
    fptr = fopen("binaryFile.txt ","r");
    newF = fopen("hexaDecimal.txt","w");
    fgets(line,lengthLine,fptr);
    while (!feof(fptr))
    {
        insertHexa(line,newF);
        fgets(line,lengthLine,fptr);
        
    }
    fclose(fptr);
    fclose(newF);
}
void insertHexa(char line[lengthLine],FILE *newF)
{
    char hexa[18];
    char binary[4];
    int number;
    int i = 0;
    int j = 4;
    hexa[18] = line[0];
    hexa[17] = line[1];
    hexa[16] = line[2];
    hexa[15] = line[3];
    hexa[14] = 'A';
    hexa[12] = '-';
    hexa[11] = 'B';
    hexa[9] = '-';
    hexa[8] = 'C';
    hexa[6] = '-';
    hexa[5] = 'D';
    hexa[3] = '-';
    hexa[2] = 'E';
    for(j;j<8;j++)
    {
        binary[i] = line[j];
        i++;
    }
    number = binaryConvert(binary);
    i = 0;
    hexa[13] = numberToHexca(number);
    for(j;j<12;j++)
    {
        binary[i] = line[j];
        i++;
    }
    number = binaryConvert(binary);
    i = 0;
    hexa[10] = numberToHexca(number);
    for(j;j<16;j++)
    {
        binary[i] = line[j];
        i++;
    }
    number = binaryConvert(binary);
    i = 0;
    hexa[7] = numberToHexca(number);
    for(j;j<20;j++)
    {
        binary[i] = line[j];
        i++;
    }
    number = binaryConvert(binary);
    i = 0;
    hexa[4] = numberToHexca(number);
    for(j;j<24;j++)
    {
        binary[i] = line[j];
        i++;
    }
    number = binaryConvert(binary);
    hexa[1] = numberToHexca(number);
    insertToFile(newF,hexa);

}
void insertToFile(FILE *fptr,char hexa[18]) //this method print to file the binary table 
{    
    fprintf(fptr,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",hexa[18]
    ,hexa[17],hexa[16],hexa[15],hexa[14],hexa[13],hexa[12],hexa[11]
    ,hexa[10],hexa[9],hexa[8],hexa[7],hexa[6],hexa[5]
    ,hexa[4],hexa[3],hexa[2],hexa[1],hexa[0]);
}
int binaryConvert(char line[4])
{
    //int i = 4;
    int hexadecimalval = 0;
    int i = 1;
    int remainder;
    int binaryval;
    binaryval = atoi(line);
    while (binaryval != 0)
    {
        remainder = binaryval % 10;
        hexadecimalval = hexadecimalval + remainder * i;
        i = i * 2;
        binaryval = binaryval / 10;
    }
    //printf("Equivalent hexadecimal value: %lX", hexadecimalval);
    return hexadecimalval;
}
char numberToHexca(int number)
{
    
    if (number == 0)
    {
        return '0';
    }
    else if (number == 1)
    {
        return '1';
    }
    else if (number == 2)
    {
        return '2';
    }
    else if (number == 3)
    {
        return '3';
    }
    else if (number == 4)
    {
        return '4';
    }
    else if (number == 5)
    {
        return '5';
    }
    else if (number == 6)
    {
        return '6';
    }
    else if (number == 7)
    {
        return '7';
    }
    else if (number == 8)
    {
        return '8';
    }
    else if (number == 9)
    {
        return '9';
    }
    else if (number == 10)
    {
        return 'a';
    }
    else if (number == 11)
    {
        return 'b';
    }
    else if (number == 12)
    {
        return 'c';
    }
    else if (number == 13)
    {
        return 'd';
    }
    else if (number == 14)
    {
        return 'e';
    }
    else if (number == 15)
    {
        return 'f';
    }
    return number;
    
}
