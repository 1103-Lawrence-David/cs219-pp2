#include "helpers.h"
#define SIZE 200

//This function process the raw data and calls the corresponding category of operation processing
// It also calls the error checking to make sure its valid
void processInstruction(ifstream& fp, int& length, uint32_t** m, uint32_t** r, int* opArr, int& flagZ){
    string fpString, operation, operand1 = "err", operand2 = "err", operand3 = "err";
    char tempChar;
    int opCount;
    bool err;

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
             //cout << "arithmetic good" << endl; //debug
            if(err == true){
                arithOp(r, operation, operand1, operand2, operand3, flagZ, err);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err);
        }
        else if(operation == "AND" || operation == "OR" || operation == "XOR"){
            if(err == true){
                bitwiseOp(r, operation, operand1, operand2, operand3, err);
            }
            display(r, m, operation, operand1, operand2, operand3, flagZ, err);
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
void display(uint32_t** r, uint32_t** m, string operation, string operand1, string operand2, string operand3, int flagZ, bool err){
    uint32_t temp;
    cout << operation  << " ||||| " << operand1;
        if(operand2 != " ||||| "){
            cout << " ||||| " << operand2;
        }
        if(operand3 != " ||||| "){
           cout << " ||||| " << operand3 << endl;
        }
        if(operation == "CMP"){
            cout << "N= n/a, Z = " << flagZ << " C= n/a, v=n/a" << endl;
        }
    if(err == true){
        cout << "Register array:" << endl;
        for(int i = 0; i < 8; i++){
            temp = *r[i];
            cout << "R" << i << " =" << std::hex << temp << "|||";
        }
        cout << endl << "Memory Array:" << endl;
        
        for(int i = 0; i < 5; i++){ //maybe update this??
            cout << *m[i] << "  ";
        }
    }
    cout << endl << endl;
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
        //cout << "Stoi: " << temp1 << endl; //debug
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
       // cout << "Stoi: " << temp2 << endl; //debug
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

//add, sub, cmp, mov
void arithOp(uint32_t** rArr, string operation, string op1, string op2, string op3, int& z, bool& err){
    uint32_t temp1, temp2;
    int regNum = 0;
    
    if(operation == "ADD"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        if(temp1 != 0 && temp2 != 0){
            *rArr[regNum] = (temp1+temp2);
        }
        else{
            cout << "Error: can not add 0 to a register." << endl;
            err = false;
        }
       // cout << "ADDING TEST: " << *rArr[regNum] << endl; //debug
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
        //cout << "MOVING TEST: " << *rArr[regNum] << endl; //debug
    }

    if(operation == "SUB"){
        regNum = findRegNum(op1);
        conversion(rArr, op2, op3, temp1, temp2);
        if(temp1 != 0 && temp2 != 0){
            *rArr[regNum] = (temp1-temp2);
        }
        else{
            err = false;
        }
        //cout << "SUB TEST: " << *rArr[regNum] << endl; //debug
    }
    if(operation == "CMP"){
        regNum = findRegNum(op1);
        conversion(rArr, op1, op2, temp1, temp2);
        if((temp1 - temp2) == 0){
            z = 1;
        }
        else{
            z = 0;
        }
    }
}

void bitwiseOp(uint32_t** r, string operation, string op1, string op2, string op3, bool& err){
    uint32_t temp1, temp2;
    int regNum = 0;
    if(operation == "AND"){
        regNum = findRegNum(op1);
        conversion(r, op2, op3, temp1, temp2);
        cout << temp1 << temp2 << endl; //debugging
        cout << (temp1&temp2) << endl;
        *r[regNum] = (temp1 & temp2);
    }
    if(operation == "XOR"){
        regNum = findRegNum(op1);
        conversion(r, op2, op3, temp1, temp2);
        cout << temp1 << temp2 << endl; //debugging
        cout << std::hex << (temp1 ^ temp2) << endl;
        *r[regNum] = (temp1 ^ temp2);
    }
    if(operation == "OR"){
         regNum = findRegNum(op1);
        conversion(r, op2, op3, temp1, temp2);
        cout << temp1 << temp2 << endl; //debugging
        cout << (temp1&temp2) << endl;
        *r[regNum] = (temp1 | temp2);
    }
}

bool errorCheck(string operation, string o1, string o2, string o3, int opNum){
     //cout << "error called" << endl; //debug
    if(opNum > 3 || opNum == 0){
        //cout << "add error message idjiot" << endl;
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
        //cout << "succ" << endl; //debug
        return true;
    }
    cout << "error in error check" << endl; 
    return false;
}

void opCount(int* opArr, ifstream& fptr){
    string fpstring, tempStore;
    char c, prevC;
    int count =0, length = 0;
    while(getline(fptr, fpstring)){
        count = 0;
        prevC = 'p';
        stringstream ss(fpstring);
        while(ss.get(c) && c != '\n'){
            if((c == '#' || c== 'R' || c =='x' || c == '_') && (prevC != 'O' && prevC != '0')){
                count++;
            }
             prevC = c;
        }
        opArr[length] = count;
        length++;
    }
    //cout << "success" << endl; //debugging
}