SRC=main.cpp
INPUT=input.asm
INTERM=intermediate.data

all: run clean

run: compile
		./run ${INPUT} ${INTERM}

compile:
		g++ ${SRC} -o run

clean:
		rm -rf run