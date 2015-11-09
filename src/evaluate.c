#include "evaluate.h"

#include <stdlib.h>
#include <inttypes.h>

#include "defines.h"

#include "tokens.h"
#include "parser.h"

#include "numStack.h"

#include "operStack.h"

#define checkNumStack(n); if (numNum < n) { fprintf(stderr, "No enough numbers: need at least %d numbers\n", n); return 0;}

Fraction lastResult = {0, 0};

int calculate();

int calculatingCycle();

int evaluate(FILE *fout, const char *expr)
{
    //parse the expression
    tokenNode *infix = createTokenNode();
    addAfterTokenNode(infix);
    if (!parse(expr, infix)) {
        fprintf(stderr, "Parsing failed\n");
        return 0;
    }

    //a flag for the +, -
    int previsnum = 0;

    initOperPriority();

    //calculate
    for (tokenNode *i = infix->next; i->token != NULL; i = i->next) {

        char *endptr = NULL;
        long long thisNumber = createNumber(i->token, &endptr);
        if (readNumErr) {
            fprintf(stderr, "Failed reading a number\n");
            freeAllTokenNodes(infix);
            return 0;
        }

        if (endptr != i->token) {

            pushNum(createFraction(thisNumber, 1));
            previsnum = 1;

        } else {

            char oper = i->token[0];
            switch (oper) {

                case '_':
                    pushNum(lastResult);
                    previsnum = 1;
                    break;

                case '(':
                    pushOper(oper);
                    previsnum = 0;
                    break;

                case ')':
                    if(!calculatingCycle()) {
                        fprintf(stderr, "Calculating failed\n");
                        freeAllTokenNodes(infix);
                        return 0;
                    }

                    //pop the (
                    popOper();
                    previsnum = 0;
                    break;

                default:

                    //dealing with the signs
                    if (!previsnum) {
                        if (oper == '+') {
                            oper = 'P';
                        } else if (oper == '-') {
                            oper = 'N';
                        }
                    }
                    
                    //there is an operator at the top of the stack
                    if (operNum) {

                        //compare the priorities of oper and topOper
                        if (operPriority[(int)oper] < operPriority[(int)getTopOper()]) {

                            //pop all and calc
                            if(!calculatingCycle()) {
                                fprintf(stderr, "Calculating failed\n");
                                freeAllTokenNodes(infix);
                                return 0;
                            }
                            pushOper(oper);

                        } else if (oper != 'P' && oper != 'N' && operPriority[(int)oper] == operPriority[(int)getTopOper()]) {

                            //pop one and calc to ensure the calulation is done l2r
                            //the P and N (aka +, -) are done r2l
                            if(!calculate()) {
                                fprintf(stderr, "Calculating failed\n");
                                freeAllTokenNodes(infix);
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
                    previsnum = 0;
                    break;
            }
        }
    }

    //pop the left operators and calc
    if(!calculatingCycle()) {
        fprintf(stderr, "Calculating failed\n");
        freeAllTokenNodes(infix);
        return 0;
    }

    //pop the result
    Fraction *result = NULL;
    switch (numNum) {
        case 0:
            fprintf(stderr, "Get no result\n");
            freeAllTokenNodes(infix);
            return 0;
        case 1:
            result = popNum();
            lastResult = *result;
            fprintf(fout, "%lld", result->numerator);
            if (result->denominator != 1) {
                fprintf(fout, "/%lld\n", result->denominator);
            } else {
                fputc('\n', fout);
            }
            break;
        default:
            fprintf(stderr, "Get multiple results\n");
            freeAllTokenNodes(infix);
            return 0;
    }

    freeAllTokenNodes(infix);

    return 1;
}

int calculate()
{
    Fraction *a = NULL, *b = NULL, c = createFraction(0, 0);

    switch (popOper()) {

        case '+':
            checkNumStack(2);
            b = popNum();
            a = popNum();

            c.numerator = a->numerator * b->denominator + b->numerator * a->denominator;
            c.denominator = a->denominator * b->denominator;

            if (c.denominator != 1 && c.denominator != 0) {
                reduce(&c);
            }
            pushNum(c);
            break;

        case '-':
            checkNumStack(2);
            b = popNum();
            a = popNum();

            c.numerator = a->numerator * b->denominator - b->numerator * a->denominator;
            c.denominator = a->denominator * b->denominator;

            if (c.denominator != 1 && c.denominator != 0) {
                reduce(&c);
            }
            pushNum(c);
            break;

        case '*':
            checkNumStack(2);
            b = popNum();
            a = popNum();

            c.numerator = a->numerator * b->numerator;
            c.denominator = a->denominator * b->denominator;

            if (c.denominator != 1 && c.denominator != 0) {
                reduce(&c);
            }
            pushNum(c);
            break;

        case '/':
            checkNumStack(2);
            b = popNum();
            a = popNum();

            c.numerator = a->numerator * b->denominator;
            c.denominator = a->denominator * b->numerator;

            if (c.denominator != 1 && c.denominator != 0) {
                reduce(&c);
            }
            pushNum(c);
            break;

        case 'P':
            checkNumStack(1);

            break;

        case 'N':
            checkNumStack(1);
            a = getTopNum();

            a->numerator *= -1;
            reduce(a);
            break;
    }

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
