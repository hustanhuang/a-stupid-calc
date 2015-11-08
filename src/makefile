compile: main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	gcc -Wall -std=c99 -g -o calc main.o evaluate.o parser.o tokens.o numStack.o operStack.o
	make clean

test: test.o number.o numberCalc.o
	gcc -Wall -std=c99 -g -o mptest test.c number.c numberCalc.c
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

test.o: number.o numberCalc.o
	gcc -c test.c

number.o:
	gcc -c number.c

numberCalc.o: number.o
	gcc -c numberCalc.c

clean:
	rm *.o *~

cleanup:
	rm -R *.dSYM
	rm calc mptest
