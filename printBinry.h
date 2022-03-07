void printBinToChar(char character,int *binaryArray);
/*
this function got string from the .string in tha assembler
and convert it to binary
*/
void codeToBinary(char *line,char *ptr);
/*
this function get all those function and uses every one 
by they time
*/
int recognizeOperands(char *array);
/*
this function return how many operand i need to get 
and then i select the function by cases
*/
void initializ(int binaryArray[20]);
/*
this function got array and intialize in zeros
*/
void initializNegativ(int binaryArray[20]);
/*
this function got array and intialize in ones
this is for the negative number
*/
void intToBinary(char num[5],int binaryArray[20]);
/*
this function convert number to binary 
*/
void intToBinary2(char *line,int num,int binaryArray[20]);
/*
this function convert base and offset number
from the simble table to binary 
*/
void numberPrint(char *line,int *binaryArray);
/*
convert the number in the line to binary and insert to line 
*/
int baseLabe(char *line);
/*
check wich simble in the line and return the base of the simble
*/
int offsetLabe(char *line);
/*
check wich simble in the line and return the offsaet of the simble
*/
int twoOperands(char *line,int *binaryArray);
/*
check wich function is it and set it in the binary line file
*/
void insertToFile();
/*
insert line to new binary file
*/
void oneOperandFunc(char *line,int *binaryArray);
/*
check wich function is it and set it in the binary line file
*/
int checkOgerInArray(char array[80]);
/*
check if there is any ogrim exist in the line
*/
int wichOger(char *line,int *binaryArray);
/*
check wich oger in the array
*/
int wichOgerMacor(char *line,int *binaryArray);
/*
insert the oger macor role to the binary line file
*/
int wichOgerYaad(char *line,int *binaryArray);
/*
insert the oger yaad role to the binary line file
*/
int wichOgerInLab(char *line,int *binaryArray);
/*
got line with simble with oger and figer it out 
the print that need to be in the binary line file
*/
int wichOgerInLabM(char *line,int *binaryArray);
/*
got line with simble with oger and figer it out 
the print that need to be in the binary line file
*/