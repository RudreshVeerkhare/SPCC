SRC=main.cpp
GRAMMER=input.grammer

all: run

run: compile
	./run ${GRAMMER} && rm -rf run

compile:
	g++ ${SRC} -o run

clean:
	rm -rf run