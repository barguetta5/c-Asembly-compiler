#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
  char lab[30];
  int value;
  int base;
  int offset;
  int atr[2];//atribute
}simbls;
void printTable(simbls tabel);
// int main()
// {
//   simbls table = {"bar",1,2,3,4};
//   printTable(table);
 
//   return 0; 
// }
void printTable(simbls tabel)
{
  if (tabel.atr[2]!= 0 )
  {
    printf("%s -> value -  %d   base - %d   offset - %d  atribut - %d,%d\n",tabel.lab,tabel.value
     ,tabel.base,tabel.offset,tabel.atr[1],tabel.atr[2]);
  }
  else
  printf("%s -> value -  %d   base - %d   offset - %d  atribut - %d,%d\n",tabel.lab,tabel.value
     ,tabel.base,tabel.offset,tabel.atr[1]);
  
} 
int exist(simbls *lables,char lab[30],int len,int code)
{ 
  int i;
  for (i = 0; i < len; i++)
  {
    if (strstr(lables[i].lab,lab) != 0)
    {
      lables[i].atr[2] = code;
      return 1;
    }
  }
  return 0;
}
