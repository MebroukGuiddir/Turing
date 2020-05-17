LIB=-lfl
CC=gcc

all: turing

fonctions.c:	fonctions.h
	$(CC) -c fonctions.c

turing.c: turing.lex
	flex -oturing.c turing.lex

turing: turing.c fonctions.c fonctions.h
	$(CC) -Wall -o turing turing.c fonctions.c $(LIB)

clean:
	rm calc calc.tab.c lex.yy.c calc.tab.h calc.output
