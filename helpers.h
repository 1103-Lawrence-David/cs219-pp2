#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <fstream>
using namespace std;

void cleanUp(string&, string&, string&);

void display(uint32_t**, uint32_t**, string, string, string, string, int, bool, bool);

void processInstruction(ifstream&, int&, uint32_t**, uint32_t**, int*, int&);

void arithOp(uint32_t**, string, string, string, string, int&, bool&);

void conversion(uint32_t**, string, string, uint32_t&, uint32_t&);

int findRegNum(string);

void bitwiseOp(uint32_t**, string, string, string, string, bool&);

void dataTrans(uint32_t**, uint32_t**, string, string, string, bool&);

void branchOp(string, string, int);

bool errorCheck(string, string, string, string, int);

void opCount(int*, ifstream&);