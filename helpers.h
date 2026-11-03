#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <fstream>

using namespace std;
void cleanUp(string&, string&, string&);

void processInstruction(ifstream&, int&, uint32_t*, uint32_t*);

void arithOp(uint32_t*, string, string, string, string);

void conversion(uint32_t*, string, string, uint32_t&, uint32_t&);

int findRegNum(string );

//bitwiseOp

//dataTrans

//branchOp

bool errorCheck(string, string, string, string, int);