execute: main.o
	g++ -o execute main.o

main.o: helpers.h main.cpp
	g++ -c main.cpp

make clean:
	rm *.o execute