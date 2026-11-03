#include "helpers.h"
#define SIZE 200
//I am so sorry about everything being in one file, i know its a pain to go through

//This function process the raw data and calls the corresponding category of operation processing
// It also calls the error checking to make sure its valid
void processInstruction(ifstream& fp, int& length, uint32_t** m, uint32_t** r, int* opArr, int& flagZ){
    string fpString, operation, operand1 = "err", operand2 = "err", operand3 = "err";
    char tempChar;
    int opCount;
    bool err, isBranch = false;

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
        err = errorCheck(operation, operand1, operand2, operand3, opArr[length]);
        if(operation == "ADD" || operation == "SUB" || operation == "CMP" || operation == "MOV"){
            isBranch = false;
            if(err == true){
                arithOp(r, operation, operand1, operand2, operand3, flagZ, err);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err, isBranch);
        }
        else if(operation == "AND" || operation == "OR" || operation == "XOR"){
            isBranch = false;
            if(err == true){
                bitwiseOp(r, operation, operand1, operand2, operand3, err);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err, isBranch);
        }
        else if(operation == "LOAD" || operation == "STORE"){
            isBranch = false;
            if(err == true){
                dataTrans(r, m, operation, operand1, operand2, err);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err, isBranch);
        }
        else if(operation == "BAL" || operation == "BEQ" || operation == "BNE"){
            isBranch = true;
            if(err == true){
                branchOp(operation, operand1, flagZ);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err, isBranch);
            
        }
        else{
            cout << "Invalid operation error" << endl;
        }
    
        operation = "NULL";
        opCount = 0;
        
        operand1 = "err";
        operand2 = "err";
        operand3 = "err";
        
        length++;
    }

}

//This handles the logic for properly displaying output depending on which operation and if it triggered errors
void display(uint32_t** r, uint32_t** m, string operation, string operand1, string operand2, string operand3, int flagZ, bool err, bool isBranch){
    uint32_t temp;
    cout << operation  << " ||||| " << operand1;
        if(operand2 != " ||||| "){
            cout << " ||||| " << operand2;
        }
        if(operand3 != " ||||| " && operand3 != ""){
           cout << " ||||| " << operand3;
        }
        cout << endl;
        if(operation == "CMP"){
            cout << "N= n/a, Z = " << flagZ << " C= n/a, v=n/a" << endl;
        }
    if(err == true && isBranch == false){
        cout << "Register array:" << endl;
        for(int i = 0; i < 8; i++){
            temp = *r[i];
            cout << "R" << i << " = 0x" << std::hex << temp << "|||";
        }
        cout << endl << "Memory Array:" << endl;
        
        for(int i = 0; i < 5; i++){
            cout << "0x" << *m[i] << ",  ";
        }
    }
    cout << endl << endl;
}

//this cleans up and properly seperates the operand variables
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

//Helper function to handle inserting into register and memory arrays
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
    if(s == "0x100"){
        return 0;
    }
    if(s == "0x104"){
        return 1;
    }
    if(s == "0x108"){
        return 2;
    }
    if(s == "0x10c"){
        return 3;
    }
    if(s == "0x120"){
        return 4;
    }
    return 8;
}

//converts operands values into their proper values, then stores them to temp so as not to lose any data
void conversion(uint32_t** rArr, string op2, string op3, uint32_t& temp1, uint32_t& temp2){
    int regNum; 
    string manip;

    if(op2.size() >= 1 && op2[0] == 'R'){
        regNum = findRegNum(op2);
        temp1 = *rArr[regNum];
    }
    else if(!op2.empty() && op2[1] == 'x'){
        manip = op2;
        if(manip.size() >= 1 && manip[0] == '#'){
            manip = manip.substr(1);
        }
        if(manip.find("0x") != string::npos){
            manip = manip.substr(2);
            temp1 = stoi(manip, nullptr, 16);
        }
        else{
            temp1 = stoi(manip,nullptr,10);
        }
    }
    else if(!op2.empty()){
        manip = op2;
        if(manip[0] == '#'){
            manip = manip.substr(1);
        }
        if(!manip.empty() && isdigit(manip[0])){
            temp1 = stoi(manip, nullptr, 10);
        }
    }


    if(!op3.empty() && op3[0] == 'R'){
        regNum = findRegNum(op3);
        temp2 = *rArr[regNum];
    }
    else if(!op3.empty() && op3[1] == 'x'){
        manip = op3;
        if(!op3.empty() && manip[0] == '#'){
            manip = manip.substr(1);
        }
        if(manip.find("0x") != string::npos){
            manip = manip.substr(2);
            temp2 = stoi(manip, nullptr, 16);
        }
        else{
            temp2 = stoi(manip,nullptr,10);
        }
    }
    else{
        manip = op3;
        if(!op3.empty() && manip[0] == '#'){
            manip = manip.substr(1);
        }
        if(isdigit(manip[0])){
            temp2 = stoi(manip, nullptr, 10);
        }
    }
    

}

//This function takes in ADD, MOV, SUB and CMP operations and performs them accordingly.
void arithOp(uint32_t** rArr, string operation, string op1, string op2, string op3, int& z, bool& err){
    uint32_t temp1, temp2;
    int regNum = 0;
    
    if(operation == "ADD"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        if(op2[0] == 'R'){
            *rArr[regNum] = (temp1+temp2);
        }
        else{
            cout << "Error: operand 2 can not be an immediate value." << endl;
            err = false;
        }
    }
    if(operation == "MOV"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        if(regNum >= 0 && regNum <= 7){
            *rArr[regNum] = temp1;
        }
        else{
            cout << "cannot insert into a register that does not exist" << endl;
            err = false;
        }
    }

    if(operation == "SUB"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        if(op2[0] == 'R'){
            *rArr[regNum] = (temp1-temp2);
        }
        else{
            err = false;
            cout << "Error: operand 2 can not be an immediate value" << endl;
        }
    }
    if(operation == "CMP"){
        regNum = findRegNum(op1);
        conversion(rArr, op1, op2, temp1, temp2);
        if(op1[0] == 'R'){
            if((temp1 - temp2) == 0){
                z = 1;
            }
            else{
                z = 0;
            }
        }
        else{
            err = false;
            cout << "Error: operand 1 can not be an immediate value" << endl;
        }
    }
}

//This function takes AND, OR, and XOR, and performs those operations and stores in destination register.
void bitwiseOp(uint32_t** r, string operation, string op1, string op2, string op3, bool& err){
    uint32_t temp1, temp2;
    int regNum = 0;
    if(operation == "AND"){
        if(op2[0] == 'R'){
            regNum = findRegNum(op1);
            conversion(r, op2, op3, temp1, temp2);
            *r[regNum] = (temp1 & temp2);
        }
        else{
            err = false;
            cout << "Error: Operand 2 can not be an immediate value." << endl;
        }
    }
    if(operation == "XOR"){
        if(op2[0] == 'R'){
            regNum = findRegNum(op1);
            conversion(r, op2, op3, temp1, temp2);
            *r[regNum] = (temp1 ^ temp2);
        }
        else{
            err = false;
            cout << "Error: Operand 2 can not be an immediate value." << endl;
        }
    }
    if(operation == "OR"){
        if(op2[0] == 'R'){
            regNum = findRegNum(op1);
            conversion(r, op2, op3, temp1, temp2);
            *r[regNum] = (temp1 | temp2);
        }
        else{
            err = false;
            cout << "Error: Operand 2 can not be an immediate value." << endl;
        }
    }
}

//This function takes and executes LOAD and STORE functions.
void dataTrans(uint32_t** r, uint32_t** m, string operation, string op1, string op2, bool& err){
    int regNum;
    uint32_t temp1, temp2;
    if(operation == "LOAD"){
        regNum = findRegNum(op2);
        if(regNum >=0 && regNum <= 4){
            temp1 = *m[regNum];
            regNum = findRegNum(op1);
            if(regNum >=0 && regNum <= 7){
                *r[regNum] = temp1;
            }
            else{
                err = false;
                cout << "Destination register of LOAD is invalid." << endl;
            }
        }
        else{
            err = false;
            cout << "Memory address is out of range." << endl;
        }
    }
    else if(operation == "STORE"){
        regNum = findRegNum(op1);
        if(regNum >= 0 && regNum <=7){
            temp1 = *r[regNum];
            regNum = findRegNum(op2);
            if(regNum >= 0 && regNum <= 4){
                *m[regNum] = temp1;
            }
            else{
                err = false;
                cout << "destination memory address is out of range" << endl;
            }
        }
        else{
            err = false;
            cout << "Source register does not exist!" << endl;
        }
    }
    else{
        cout << "Data trans func failed catastrophically!" << endl;
    }
}

//This takes a branching statement and outputs the corresponding statement to itself and the z flag.
void branchOp(string operation, string operand, int flagZ){
    if(operation == "BEQ" && flagZ == 1){
        cout << "Branch will be taken to <" << operand << ">" << endl;
    }
    else if(operation == "BEQ" && flagZ == 0){
        cout << "Branch will not be taken to <" << operand << ">" << endl;
    }
    else if(operation == "BNE" && flagZ == 0){
        cout << "Branch will be taken to <" << operand << ">" << endl;
    }
    else if(operation == "BNE" && flagZ == 1){
        cout << "Branch will not be taken to <" << operand << ">" << endl;
    }
    else if(operation == "BAL"){
        cout << "Branch will be taken to <" << operand << ">" << endl;
    }
    else{
        cout << "There was an error displaying the branching operation." << endl;
    }
}

//This function takes the operation and opNum, and if it is the incorrect amount prints an error statement and returns corresponding bool.
bool errorCheck(string operation, string o1, string o2, string o3, int opNum){
    if(opNum > 3 || opNum == 0){
        cout << "Error: incorrect operand ammount" << endl;
        return false;
    }
    else if(opNum != 3 && (operation == "AND" || operation == "ADD" || operation == "SUB" || operation == "OR" || operation == "XOR")){
        cout << "error in operand amount" << endl;
        return false;
    }
    else if(opNum != 2 && (operation == "MOV" || operation == "CMP" || operation == "LOAD" || operation == "STORE")){
         cout << "error in operand amount" << endl;
        return false;
    }
    else if(opNum != 1 && (operation == "BNE" || operation == "BAL" || operation == "BEQ")){
         cout << "error in operand amount" << endl;
        return false;
    }
    else{
        return true;
    }
    cout << "Debugging: catastrophic error in boolErrorCheck()" << endl; 
    return false;
}

//This is a function that finds how many operands are in each statement. 
void opCount(int* opArr, ifstream& fptr){
    string fpstring, tempStore;
    char c;
    int count =0, length = 0;
    while(getline(fptr, fpstring)){
        count = 0;
        stringstream ss(fpstring);
        while(ss.get(c) && c != '\n'){
            if(c == ','){
                count++;
            }
        }
        opArr[length] = count + 1;
        length++;
    }
}