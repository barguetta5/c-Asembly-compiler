// typedef struct Node
// {
//   char lab[30];
//   int value;
//   int base;
//   int offset;
//   int atr[2];// 1 = external , 2 = entry , 3 = code , 4 =  data
// }simbls;

void printTable();
/*
    this methode got simble and print it
*/
int exist();
/*
    this method check if the simble exist
    and inserting the atrebute by the rules
    example: if the simble was initialized by atr - code
                and now there is another one on entry 
                so its gonna add just entry to the atribute and not
                all the arguments
*/