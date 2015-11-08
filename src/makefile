compile: main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	gcc -Wall -std=c99 -g -o calc main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	make clean

main.o: evaluate.o
	gcc -c main.c

evaluate.o: parser.o tokens.o numStack.o operStack.o
	gcc -c evaluate.c

parser.o: tokens.o
	gcc -c parser.c

tokens.o:
	gcc -c tokens.c

numStack.o:
	gcc -c numStack.c

operStack.o:
	gcc -c operStack.c

clean:
	rm *.o *~

cleanup:
	rm calc 
	rm -R calc.dSYM
