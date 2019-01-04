all: prog1 prog2 

prog1: prog1.o prog1.h
	g++ -o prog1 -Wall -g prog1.o -I/postgresql -lpq
prog1.o: prog1.cc prog1.h functions.cc
	g++ -c -Wall -g  prog1.cc -I/postgresql -lpq
prog2: prog2.o prog2.h functions.cc
	g++ -o prog2 -Wall -g prog2.o -I/postgresql -lpq
prog2.o: prog2.cc prog2.h
	g++ -c -Wall -g prog2.cc -I/postgresql -lpq
clean:
	rm -f prog1.o Makefile~ prog1 prog1.cc~ prog1.h~ prog2.o prog2 prog2.cc~ prog2.h~ functions.cc~ 
