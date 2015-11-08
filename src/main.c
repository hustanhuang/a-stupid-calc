#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "defines.h"
#include "evaluate.h"

int main (int argc, char **argv)
{
    FILE *fin = stdin;
    FILE *fout = stdout;

    //-e enables the evaluating mode
    int eflag = 0;
    int fflag = 0;

    //expr stores the expression to evaluate
    char *expr = NULL;

    //standard option processing loop
    opterr = 0;
    int c = 0;
    while ((c = getopt (argc, argv, "f:o:e:")) != -1) {
        switch (c) {
            case 'e':
                eflag = 1;
                expr = optarg;
                break;
            case 'f':
                fin = fopen(optarg, "r");
                if(!fin) {
                    perror("file opening failed");
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
                fout = fopen(optarg, "w");
                if(!fout) {
                    perror("file opening failed");
                    return EXIT_FAILURE;
                }
                break;
            case '?':
                if (optopt == 'e')
                    fprintf(stderr, "Evaluating mode requires at least an expression\n");
                else if (optopt == 'f')
                    fprintf(stderr, "No input file\n");
                else if (optopt == 'o')
                    fprintf(stderr, "No output file\n");
                else
                    fprintf (stderr, "Option Error\n");
                return EXIT_FAILURE;
            default:
                fprintf(stderr, "Unknown error\n");
                return EXIT_FAILURE;
        }
    }

    //the EVALUATING mode
    if (eflag) {

        //evaluate the first expression
        fprintf(fout, "%s = ", expr);
        if (!evaluate(fout, expr)) {
            fprintf(stderr, "Evaluation failed\n");
        }

        //evaluate the rest expressions (if there is any)
        int i = optind;
        while (i != argc) {

            expr = argv[i];

            fprintf(fout, "%s = ", expr);
            if (!evaluate(fout, expr)) {
                fprintf(stderr, "Evaluation failed\n");
            }

            ++i;
        }

    //the INTERACTIVE mode
    } else {
 
        //interactive mode emulates the python interpreter
        if (fout == stdout) {
            fprintf(fout, "A Stupid Calc\n");
        }

        //interactive mode does not evaluate the expressions from the parameters
        if (optind != argc) {
            fprintf(fout, "The expressions in the parameters are ignored.\n");
        }

        //the max available length is defined by maxExprLen in defines.h
        expr = malloc(sizeof(char) * maxExprLen);

        while (1) {

            //print prompt
            if (fout == stdout) {
                fprintf(fout, ">>> ");
            }

            //initialize the expression space
            memset(expr, 0, sizeof(char) * maxExprLen);

            //when entering the EOF, scanf may enter a infinite loop
            //this test solves this problem
            if (scanf("%s", expr) != EOF) {

                if (!evaluate(fout, expr)) {
                    fprintf(stderr, "Evaluation failed\n");
                }

            } else {

                //if encountered EOF then break the loop and quit
                if (fout == stdout) {
                    fprintf(fout, "exit\n");
                } else {
                    fputc(EOF, fout);
                }
                break;
            }
        }

        //free the allocated memories
        free(expr);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
