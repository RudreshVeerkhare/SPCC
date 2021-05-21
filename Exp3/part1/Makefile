SRC=main.cpp
TARGET=sample.txt
GRAMMER=input.grammer

all: run

run: compile
	./run ${GRAMMER} ${TARGET} && rm -rf run

compile:
	g++ ${SRC} -o run

clean:
	rm -rf run