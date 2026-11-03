execute: main.o helpers.o
	g++ -o execute main.o helpers.o

main.o: helpers.h main.cpp 
	g++ -c main.cpp

helpers.o: helpers.h helpers.cpp
	g++ -c helpers.cpp
	
make clean:
	rm *.o execute