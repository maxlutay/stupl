
SHELL=C:/Windows/System32/cmd.exe

CC=clang++ 
CFLAGS=--std=c++20

all: main


build_main:
	$(CC) $(CFLAGS) main_langdemo.cpp -o main_langdemo.exe


main: build_main
	main_langdemo.exe


build_problem:
	$(CC) $(CFLAGS) misc/problem.cpp -o problem.exe

problem: build_problem
	problem.exe
