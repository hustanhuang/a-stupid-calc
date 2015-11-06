#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "defines.h"
#include "evaluate.h"

int main (int argc, char **argv)
{
    //-e enables the evaluating mode
    int eflag = 0;

    //expr stores the expression to evaluate
    char *expr = NULL;

    //standard option processing loop
    opterr = 0;
    int c = 0;
    while ((c = getopt (argc, argv, "e:")) != -1) {
        switch (c) {
            case 'e':
                eflag = 1;
                expr = optarg;
                break;
            case '?':
                if (optopt == 'e')
                    fprintf (stderr, "Evaluating mode requires at least an expression\n");
                else
                    fprintf (stderr, "Option Error\n");
                return 1;
            default:
                fprintf(stderr, "Unknown error\n");
                return 1;
        }
    }

    //the EVALUATING mode
    if (eflag) {

        //evaluate the first expression
        if (!evaluate(expr)) {
            fprintf(stderr, "Evaluation failed\n");
        }

        //evaluate the rest expressions (if there is any)
        int i = optind;
        while (i != argc) {

            expr = argv[i];
            if (!evaluate(expr)) {
                fprintf(stderr, "Evaluation failed\n");
            }

            ++i;
        }

    //the INTERACTIVE mode
    } else {
 
        //interactive mode emulates the python interpreter
        printf("A Stupid Calc\n");

       
        //interactive mode does not evaluate the expressions from the parameters
        if (optind != argc) {
            printf("The expressions in the parameters are ignored.\n");
        }

        //the max available length is defined by maxExprLen in defines.h
        expr = malloc(sizeof(char) * maxExprLen);

        while (1) {

            //print prompt
            printf(">>> ");

            //initialize the expression space
            memset(expr, 0, sizeof(char) * maxExprLen);

            //when entering the EOF, scanf may enter a infinite loop
            //this test solves this problem
            if (scanf("%s", expr) != EOF) {

                if (!evaluate(expr)) {
                    fprintf(stderr, "Evaluation failed\n");
                }

            } else {

                //if encountered EOF then break the loop and quit
                printf("exit\n");
                break;
            }
        }

        //free the allocated memories
        free(expr);
    }
    return 0;
}
