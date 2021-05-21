LAX_FILE=main.lex
TARGET=sample.pas

all: run

run: compile
	./pascalLex ${TARGET}

compile: lex
	gcc lex.yy.c -o pascalLex && rm -rf lex.yy.c

lex:
	lex ${LAX_FILE}

clean:
	rm -rf lex.yy.c
