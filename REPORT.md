HOW TO RUN CODE/ COMMANDS:

This code was compiled and ran successfully on a windows 11 laptop in vscode using WSL in an ubuntu environment.

make: compiles the program.

./execute: runs the program

make clean: removes all .o files and execute.

There is no user interface, and this program requires the "pp_2input.txt" file to run. If you would like to edit and test new implementations, please edit that text file.

LOGIC/FUNCTIONALITY OF OPERATIONS:

ADD: Finds the location of register 1 in rArr. then coverts the values in op2 and op3 (regardless if they are registers or immediates) into hex. If op2 is a register and not an immediate value, the destination register is updated to hold the value of temp1+temp (the two hex values). Otherwise, outputs an error.

MOV: Finds the location of register 1 in rArr. then coverts the values in op2 and op3 (regardless if they are registers or immediates) into hex, though op3 is disregarded in this case. If the destination register is a valid register, stores the value in the temp1 (the hex of op2) into the destination register. Otherwise, outputs an error.


SUB: Finds the location of register 1 in rArr. then coverts the values in op2 and op3 (regardless if they are registers or immediates) into hex. If op2 is a register and not an immediate value, the destination register is updated to hold the value of temp1-temp (the two hex values). Otherwise, outputs an error.

CMP:Finds the location of register 1 in rArr. then coverts the values in op2 and op3 (regardless if they are registers or immediates) into hex. If operand 1 is a register, it subtracts the 2 hex values, and checks if they equal 0. If they do, z= 1, and if they dont, z=0. Otherwise, outputs an error.

AND: If operand2 is a register and not an immediate value, finds the location of op1 in the array, converts op2 and op3 into hex (stored in temp1 and temp2), and then performs bitwise AND on temp 1 and temp2, which is then stored in the corresponding location in the array. otherwise, outputs an error.

XOR:If operand2 is a register and not an immediate value, finds the location of op1 in the array, converts op2 and op3 into hex (stored in temp1 and temp2), and then performs bitwise XOR on temp 1 and temp2, which is then stored in the corresponding location in the array. otherwise, outputs an error.

OR: If operand2 is a register and not an immediate value, finds the location of op1 in the array, converts op2 and op3 into hex (stored in temp1 and temp2), and then performs bitwise OR on temp 1 and temp2, which is then stored in the corresponding location in the array. otherwise, outputs an error.

LOAD: finds the regNum of op2. if this number is above -1 or below 5, it is valid (prints error otherwise). we then store the value in the memory array that corresponds to the regNum in a temp hex variable. we then find the reg num of op1. If this num is above -1 and below 8, we store temp1 into the corresponding location of the regNUm in the tegister array. otherwise, we output an error. 

STORE: We find the regNUm of op1. if this is above -1 and below 8, it is valid (otherwise print error). we store the corresponding value in the memory array int temp1. we now find the regNum of op2. If this  is above -1 and below 5, we store temp1 into the corresponding memory array. Otherwise, we print an error.

BEQ: If the Z flag equals 1, this will branch and prints a statement declaring such. if z= 0, It does not branch and prints a statement declaring such.

BNE: if the Z flag = 1, it does not branch and prints a statement declaring such. If the Z flag does equal 0, it branches and prints a statement declaring such.

BAL: This function prints the "will branch" statement regardless of Z value.


INVALID CASES:
If the statement has too few or too many operands, it will print incorrect operand amount.
The dataTrans func outputs 2 errors: memory address out of range, and tregister is invalid. if the memory address is less than 0x100 and more than 0x110, it will return an error. If register is less then 0 or greater than 7, it returns an error as well.
In bitwiseOp, there is one invalid case: if operand 2 is not a register value. If it is anything else, it automatically prints an error.
in arithOp, there are 2 invalid cases: if the oeprand is an immediate value (operand 2 for ADD and SUB, and operand 1 for CMP), and if the register is above r7 or below r0 for MOV.
Finally, in processInstruction, if an input operation is not named properly, it will output an error statement.
There are miscellaneous error statements that are mainly meant for bug testing. These can be ignored.