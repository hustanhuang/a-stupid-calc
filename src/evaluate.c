#include "evaluate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"

#include "tokens.h"
#include "parser.h"

#include "number.h"
#include "numberCalc.h"
#include "numStack.h"

#include "operStack.h"

#define checkNumStack(); if (numNum < 2) { fprintf(stderr, "No enough numbers\n"); return 0;}

int calculate();

int calculatingCycle();

int evaluate(const char *expr)
{
    //parse the expression
    tokenNode *infix = createTokenNode();
    addAfterTokenNode(infix);
    if (!parse(expr, infix)) {
        fprintf(stderr, "Parsing failed\n");
        return 0;
    }

    initOperPriority();

    //calculate
    for (tokenNode *i = infix->next; i->token != NULL; i = i->next) {

        char *endptr = NULL;
        long long thisNumber = strtoll(i->token, &endptr, 0);

        if (endptr != i->token) {

            pushNum(createFraction(thisNumber, 1));

        } else {

            const char oper = i->token[0];
            switch (oper) {

                case '(':
                    pushOper(oper);
                    break;

                case ')':
                    if(!calculatingCycle()) {
                        fprintf(stderr, "Calculating failed\n");
                        return 0;
                    }

                    //pop the (
                    popOper();
                    break;

                default:

                    //there is an operator at the top of the stack
                    if (operNum) {

                        //compare the priorities of oper and topOper
                        if (operPriority[(int)oper] < operPriority[(int)getTopOper()]) {

                            //pop all and calc
                            if(!calculatingCycle()) {
                                fprintf(stderr, "Calculating failed\n");
                                return 0;
                            }
                            pushOper(oper);

                        } else if (operPriority[(int)oper] == operPriority[(int)getTopOper()]) {

                            //pop one and calc to ensure the calulation is done l2r
                            if(!calculate()) {
                                fprintf(stderr, "Calculating failed\n");
                                return 0;
                            }
                            pushOper(oper);

                        } else {
                            pushOper(oper);
                        }

                    //the operator stack is empty
                    } else {
                        pushOper(oper);
                    }
                    break;
            }
        }
    }

    //pop the left operators and calc
    if(!calculatingCycle()) {
        fprintf(stderr, "Calculating failed\n");
        return 0;
    }

    //pop the results
    while (numNum) {
        Fraction *result = popNum();
        printf("%lld", result->numerator);
        if (result->denominator == 1) {
            putchar('\n');
        } else {
            printf("%lld\n", result->denominator);
        }
    }

    //free the tokens allocated
    freeAllTokenNodes(infix);

    return 1;
}

int calculate()
{
    checkNumStack();
    Fraction *b = popNum();
    Fraction *a = popNum();
    Fraction c = createFraction(0, 0);

    switch (popOper()) {
        case '+':
            c.numerator = a->numerator * b->denominator + b->numerator * a->denominator;
            c.denominator = a->denominator * b->denominator;
            break;
        case '-':
            c.numerator = a->numerator * b->denominator - b->numerator * a->denominator;
            c.denominator = a->denominator * b->denominator;
            break;
        case '*':
            c.numerator = a->numerator * b->numerator;
            c.denominator = a->denominator * b->denominator;
            break;
        case '/':
            c.numerator = a->numerator * b->denominator;
            c.denominator = a->denominator * b->numerator;
            break;
    }
    reduce(&c);

    pushNum(c);

    return 1;
}


int calculatingCycle()
{
    while (getTopOper() != '(' && operNum) {
        if (!calculate()) {
            fprintf(stderr, "Failed when doing operation %c\n", getTopOper());
            return 0;
        }
    }

    return 1;
}
