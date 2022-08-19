all : format build clean

format:
	clang-format -i *.c *.h

build:
	gcc -O2 -c main.c -o main.o
	gcc -O2 -c vector.c -o vector.o
	gcc main.o vector.o -o Exe

clean:
	rm *.o
