#include "helpers.h"
#define SIZE 200

//This function process the raw data and calls the corresponding category of operation processing
// It also calls the error checking to make sure its valid
void processInstruction(ifstream& fp, int& length){
    string fpString, operation, operand1, operand2, operand3;
    char tempChar;
    int opCount;

    while(getline(fp, fpString)){
        stringstream ss(fpString);
        ss >> operation;
        ss.get(tempChar);
        if(tempChar == ' '){
            opCount = 1; 
            ss >> operand1;
        }

        ss.get(tempChar);
        if(tempChar == ' '){
            opCount = 2; 
            ss >> operand2;
        }

        ss.get(tempChar);
        if(tempChar == ' '){
            opCount = 3; 
            ss >> operand3;
        }
        
        ss.get(tempChar);
        if(tempChar == ' '){
            opCount = 4; 
        }

        if(operation == "ADD" || operation == "SUB" || operation == "CMP" || operation == "MOV"){
            //call arithmetic func
            
        }
        else if(operation == "AND" || operation == "OR" || operation == "XOR"){
            //CALL BITWISE

        }
        else if(operation == "LOAD" || operation == "STORE"){
            //CALL DATA TRANSER

        }
        else if(operation == "BAL" || operation == "BEQ" || operation == "BNE"){
            //CALL BRANCHING
            
        }
        else{
            cout << "Invalid operation error( fix later!)" << endl;
        }
        operation = "NULL";
        opCount = 0;
        operand1 = "err";
        operand2 = "err";
        operand3 = "err";
        length++;
    }

}