all: main.o Complex.o
	g++ -g main.o Complex.o -o program


clean: 
	rm -f *.o program
