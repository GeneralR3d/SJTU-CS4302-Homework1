
compiler=gcc

all: p1 p2 p3

p1: p1.c
	$(compiler) -g -Wall -fopenmp -o p1 p1.c

p2: p2.c
	$(compiler) -g -Wall -fopenmp -o p2 p2.c

p3: p3.c
	$(compiler) -g -Wall -fopenmp -o p3 p3.c

clean: 
	rm p1 p2 p3