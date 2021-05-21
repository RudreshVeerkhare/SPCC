SRC=main.cpp
TARGET=

all: run

run: compile
	./run ${TARGET} && rm -rf run

compile:
	g++ ${SRC} -o run

clean:
	rm -rf run