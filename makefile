
EXECUTABLE_FORMAT_PREPEND=
EXECUTABLE_FORMAT_APPEND=

ifeq ($(OS),Windows_NT)
	SHELL=C:/Windows/System32/cmd.exe
	EXECUTABLE_FORMAT_APPEND=.exe
	CLEAR_COMMAND=del
	PATH_SEPARATOR=\\

else
	CLEAR_COMMAND=rm
	PATH_SEPARATOR=/
endif

EXECUTABLE_FORMAT_PREPEND=.$(PATH_SEPARATOR)



MAIN_DIR=
ifndef MAIN_DIR
	MAIN_DIR=.
endif
EXECUTABLE_MAIN_PATH=$(MAIN_DIR)$(PATH_SEPARATOR)compiler$(EXECUTABLE_FORMAT_APPEND)


PROBLEM_DIR=test
ifndef PROBLEM_DIR
	PROBLEM_DIR=.
endif
EXECUTABLE_PROBLEM_PATH=$(PROBLEM_DIR)$(PATH_SEPARATOR)problem$(EXECUTABLE_FORMAT_APPEND)




CC=clang++ 
CFLAGS=--std=c++17



all: main


build_main:
	$(CC) $(CFLAGS) '$(MAIN_DIR)$(PATH_SEPARATOR)compiler.cpp' -o '$(EXECUTABLE_MAIN_PATH)' -I src


main: build_main
	$(EXECUTABLE_MAIN)


build_problem:
	$(CC) $(CFLAGS) $(PROBLEM_DIR)$(PATH_SEPARATOR)problem.cpp -o $(EXECUTABLE_PROBLEM_PATH) -I src

problem: build_problem
	$(EXECUTABLE_PROBLEM_PATH)



remove_problem_executable:
	$(CLEAR_COMMAND) "$(EXECUTABLE_PROBLEM_PATH)"
