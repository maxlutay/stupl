
EXECUTABLE_FORMAT_PREPEND=
EXECUTABLE_FORMAT_APPEND=

ifeq ($(OS),Windows_NT)
	SHELL=C:/Windows/System32/cmd.exe
	EXECUTABLE_FORMAT_APPEND=.exe
else 
	EXECUTABLE_FORMAT_PREPEND=./
endif


EXECUTABLE_MAIN=$(EXECUTABLE_FORMAT_PREPEND)main_langdemo$(EXECUTABLE_FORMAT_APPEND)
EXECUTABLE_PROBLEM=$(EXECUTABLE_FORMAT_PREPEND)problem$(EXECUTABLE_FORMAT_APPEND)

CC=clang++ 
CFLAGS=--std=c++20

all: main


build_main:
	$(CC) $(CFLAGS) main_langdemo.cpp -o $(EXECUTABLE_MAIN)


main: build_main
	main_langdemo.exe


build_problem:
	$(CC) $(CFLAGS) misc/problem.cpp -o $(EXECUTABLE_PROBLEM)

problem: build_problem
	problem.exe
