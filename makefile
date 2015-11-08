compile: main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	gcc -std=c99 -o calc obj/main.o obj/evaluate.o obj/parser.o obj/tokens.o obj/numStack.o obj/operStack.o

main.o: obj evaluate.o
	gcc -std=c99 -o obj/main.o -c src/main.c

evaluate.o: obj parser.o tokens.o numStack.o operStack.o
	gcc -std=c99 -o obj/evaluate.o -c src/evaluate.c

parser.o: obj tokens.o
	gcc -std=c99 -o obj/parser.o -c src/parser.c

tokens.o: obj
	gcc -std=c99 -o obj/tokens.o -c src/tokens.c

numStack.o: obj
	gcc -std=c99 -o obj/numStack.o -c src/numStack.c

operStack.o: obj
	gcc -std=c99 -o obj/operStack.o -c src/operStack.c

obj:
	rm -f -R obj
	mkdir obj
