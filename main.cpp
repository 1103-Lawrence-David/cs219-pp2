#include "helpers.h"
#define READ_FILE "pp2_input.txt"
#define SIZE 200
int main(){
    uint32_t Ox100 = 0, Ox104 = 0, Ox108 = 0, Ox10c = 0, Ox110 = 0;
    uint32_t *memArr[5] = {&Ox100, &Ox104, &Ox108, &Ox10c, &Ox110};
    uint32_t R0 = 0,  R1 = 0, R2 = 0,  R3 = 0 , R4 = 0, R5 = 0, R6 = 0, R7 = 0;
    uint32_t *regArr[8] = {&R0, &R1, &R2, &R3, &R4, &R5, &R6, &R7};
    int length = 0, operandCount[SIZE], flagZ;

    ifstream fptr(READ_FILE);
    if(!fptr.is_open()){
        cout<< "File could not be opened properly." << endl;
        return 1;
    }

    opCount(operandCount, fptr);
    fptr.close();
    ifstream fptr2(READ_FILE);
    if(!fptr2.is_open()){
        cout<< "File could not be opened properly." << endl;
        return 1;
    }
    processInstruction(fptr2, length, memArr, regArr, operandCount, flagZ);
    fptr2.close();
    return 0;
}