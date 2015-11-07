compile:
	gcc -Wall -std=c99 -g -o calc *.c
	make clean

test:
	gcc -Wall -std=c99 -g -o mptest test.c number.c numberCalc.c
	make clean

clean:
	rm *.o *~

cleanup:
	rm calc
	rm -R calc.dSYM
	make clean
