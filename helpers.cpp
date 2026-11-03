#include "helpers.h"
#define SIZE 200

//This function process the raw data and calls the corresponding category of operation processing
// It also calls the error checking to make sure its valid
void processInstruction(ifstream& fp, int& length, uint32_t* m, uint32_t* r){
    string fpString, operation, operand1 = "err", operand2 = "err", operand3 = "err";
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

        cleanUp(operand1, operand2, operand3);

        if(operation == "ADD" || operation == "SUB" || operation == "CMP" || operation == "MOV"){
            //if(errorCheck(operation, operand1, operand2, operand3, opCount)){
                //arithOp(r, operation, operand1, operand2, operand3);
           // }
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
        cout << operation << "||||" << opCount << "|||||" << operand1 << "|||||" << operand2 << "||||||" << operand3 << endl; //debugging
        operation = "NULL";
        opCount = 0;
        operand1 = "err";
        operand2 = "err";
        operand3 = "err";
        length++;
    }

}

void cleanUp(string& op1, string& op2, string& op3){
    string temp1 = "", temp2 = "", temp3 = "", rework;
    int splitCount = 1;
    bool fixEnd = false;
    if (op2 != "err") op1 += op2;
    if (op3 != "err") op1 += op3;

    for(int i = 0; i < op1.length(); i++){
        char c = op1[i];
        if(c != ' ' && c != '#' && c != ','){
            if(splitCount == 1){
                temp1 += c;
            }
            if(splitCount == 2){
                temp2 += c;
            }
            if(splitCount == 3){
                temp3 += c;
            }
        } 
        if(c == ','){
            splitCount++;
        }
    }
    op1 = temp1;
    op2 = temp2;
    op3 = temp3;
}

int findRegNum(string s){
    if(s == "R0"){
        return 0;
    }
    if(s == "R1"){
        return 1;
    }
    if(s == "R2"){
        return 2;
    }
    if(s == "R3"){
        return 3;
    }
    if(s == "R4"){
        return 4;
    }
    if(s == "R5"){
        return 5;
    }
    if(s == "R6"){
        return 6;
    }
    if(s == "R7"){
        return 7;
    }
    return 8;
}
void conversion(uint32_t* rArr, string op2, string op3, uint32_t& temp1, uint32_t& temp2){
    int regNum; 

    if(op2 == "R0" || op2 == "R1" || op2 == "R2" || op2 == "R3" || op2 == "R4" || op2 == "R5" || op2 == "R6" || op2 == "R7"){
        regNum = findRegNum(op2);
        temp1 = rArr[regNum];
    }
    if(op3 == "R0" || op3 == "R1" || op3 == "R2" || op3 == "R3" || op3 == "R4" || op3 == "R5" || op3 == "R6" || op3 == "R7"){
        regNum = findRegNum(op3);
        temp2 = rArr[regNum];
    }

}

//add, sub, cmp, mov
void arithOp(uint32_t* rArr, string operation, string op1, string op2, string op3){
    uint32_t temp1, temp2;
    int regNum = 0;
    string output;
    
    if(operation == "ADD"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        rArr[regNum] = (temp1+temp2);
    }
}

bool errorCheck(string operation, string o1, string o2, string o3, int opNum){
    if(opNum > 3 || opNum == 0){
        return false;
    }
    else if(opNum != 3 && (operation == "ADD" || operation == "SUB" || operation == "OR" || operation == "XOR")){
        return false;
    }
    else if(opNum != 2 && (operation == "MOV" || operation == "CMP" || operation == "LOAD" || operation == "STORE")){
        return false;
    }
    else if(opNum != 1 && (operation == "BNE" || operation == "BAL" || operation == "BEQ")){
        return false;
    }
    else{
        return true;
    }
    cout << "error in error check" << endl; 
    return false;
}