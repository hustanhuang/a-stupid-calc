compile: main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	gcc -Wall -std=c99 -g -o bin/calc obj/main.o obj/evaluate.o obj/parser.o obj/tokens.o obj/numStack.o obj/operStack.o

main.o: evaluate.o
	gcc -o obj/main.o -c src/main.c

evaluate.o: parser.o tokens.o numStack.o operStack.o
	gcc -o obj/evaluate.o -c src/evaluate.c

parser.o: tokens.o
	gcc -o obj/parser.o -c src/parser.c

tokens.o:
	gcc -o obj/tokens.o -c src/tokens.c

numStack.o:
	gcc -o obj/numStack.o -c src/numStack.c

operStack.o:
	gcc -o obj/operStack.o -c src/operStack.c
