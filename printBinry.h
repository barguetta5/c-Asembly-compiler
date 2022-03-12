void codeToBinary();
/*
main function on this class!!!

    this function go over the lines
    check wich function is this and wich operand he have
    and use the function in the calss to defin the binarry line code
    as recomnad in the task.

    for example : if the function need a simble so he goes to the simble table
    took out the base and offset and insert to the binary text file.
*/
void printBinToChar();
/*
this function got string from the .string in tha assembler
and convert it to binary
*/

int recognizeOperands();
/*
this function return how many operand i need to get 
and then i select the function by cases
*/
void initializ();
/*
this function got array and intialize in zeros
*/
void initializNegativ();
/*
this function got array and intialize in ones
this is for the negative number
*/
void intToBinary();
/*
this function convert number to binary 
*/
void intToBinary2();
/*
this function convert base and offset number
from the simble table to binary 
*/
void numberPrint();
/*
convert the number in the line to binary and insert to line 
*/
int baseLabe();
/*
check wich simble in the line and return the base of the simble
*/
int offsetLabe();
/*
check wich simble in the line and return the offsaet of the simble
*/
int twoOperands();
/*
check wich function is it and set it in the binary line file
*/
void insertToFile();
/*
insert line to new binary file
*/
void oneOperandFunc();
/*
check wich function is it and set it in the binary line file
*/
int checkOgerInArray();
/*
check if there is any ogrim exist in the line
*/
int wichOger();
/*
check wich oger in the array
*/
int wichOgerMacor();
/*
insert the oger macor role to the binary line file
*/
int wichOgerYaad();
/*
insert the oger yaad role to the binary line file
*/
int wichOgerInLab();
/*
got line with simble with oger and figer it out 
the print that need to be in the binary line file
*/
int wichOgerInLabM();
/*
got line with simble with oger and figer it out 
the print that need to be in the binary line file
*/