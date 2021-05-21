LEX_FILE=main.c
TARGET=sample.pas

all: run

run: compile
		./pascalLex ${TARGET} && rm -rf pascalLex

compile:
		gcc ${LEX_FILE} -o pascalLex
	
clean:
	rm -rf pascalLex