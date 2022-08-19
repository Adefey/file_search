all : format build clean test

format:
	clang-format -i *.cpp

build:
	g++ -I ../ -O2 -c main.cpp -o main.o
	gcc -I ../ -O2 -c ../vector.c -o vector.o
	g++ main.o vector.o -o ExeTest -lgtest

clean:
	rm *.o

test:
	valgrind ./ExeTest
