#include <stdio.h>
#include <stdlib.h>
static int countSimble;
typedef struct Node
{
  char lab[30];
  int value;
  int base;
  int offset;
  int atr[2];// 1 = external , 2 = entry , 3 = code , 4 =  data
}simbls;
void printTable(simbls tabel)//print the lable
{
  if (tabel.atr[1]!= 0)
  {
    printf("%s -> value -  %d   base - %d   offset - %d  atribut - %d,%d\n",tabel.lab,tabel.value
     ,tabel.base,tabel.offset,tabel.atr[0],tabel.atr[1]);
  }
  else
  printf("%s -> value -  %d   base - %d   offset - %d  atribut - %d\n",tabel.lab,tabel.value
     ,tabel.base,tabel.offset,tabel.atr[0]);
  
} 
int exist(simbls *lables,char lab[30],int len,int code,int value,int base,int offset)//check if lable exist
{ 
  int i;
  for (i = 0; i < len; i++)
  {
  
    if (strstr(lables[i].lab,lab) != 0 && lables[i].atr[0] !=0)
    {
      if (lables[i].atr[0] == 1)
      {
        lables[i].value = value;
        lables[i].base = base;
        lables[i].offset = offset;
      }
      
      lables[i].atr[1] = code;
      return 1;
    }
  }
  return 0;
}
