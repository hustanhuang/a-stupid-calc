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

#define checkNumStack(); if (numNum < 2) { fprintf(stderr, "No enough numbers.\n"); return 0;}

int evaluate(const char *expr)
{
    tokenNode *infix = createTokenNode();
    addAfterTokenNode(infix);

    if (!parse(expr, infix)) {
        fprintf(stderr, "Parsing failed\n");
        return 0;
    }

    Fraction numStack[maxExprLen];
    int numNum = 0;
    char operStack[maxExprLen];
    int operNum = 0;
    int previsNum = 0;
    int negativeFlag = 1;

    int operPriority[256];
    memset(operPriority, -1, sizeof(operPriority));

    operPriority['+'] = 0;
    operPriority['-'] = 1;
    operPriority['*'] = 2;
    operPriority['/'] = 3;

    for (tokenNode *i = infix->next; i->token != NULL; i = i->next) {

        char *endptr = NULL;
        long long thisNumber = strtoll(i->token, &endptr, 0);

        if (endptr != i->token) {

            Fraction thisFraction = { negativeFlag * thisNumber, 1 };
            printf("%lld/%lld\n", thisFraction.numerator, thisFraction.denominator);
            numStack[numNum++] = thisFraction;
            negativeFlag = 1;
            previsNum = 1;

        } else {

            const char oper = i->token[0];
            switch (oper) {

                case '(':
                    operStack[operNum++] = oper;
                    break;

                case ')':

                    while (operStack[operNum - 1] != '(' && operNum) {

                        checkNumStack();
                        Fraction *b = numStack + (--numNum);
                        printf("b = %lld/%lld\n", b->numerator, b->denominator);
                        Fraction *a = numStack + (--numNum);
                        printf("a = %lld/%lld\n", a->numerator, a->denominator);
                        Fraction c;
                        printf("%c\n", operStack[operNum - 1]);

                        switch (operStack[--operNum]) {
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

                        printf("%lld/%lld\n", c.numerator, c.denominator);

                        reduce(&c);

                        numStack[numNum++] = c;
                    }

                    --operNum;
                    break;
                default:

                    if (operNum) {

                        int operIndex = oper;
                        int topOperIndex = operStack[operNum - 1];

                        if (operPriority[operIndex] < operPriority[topOperIndex]) {

                            while (operStack[operNum - 1] != '(' && operNum) {

                                checkNumStack();
                                Fraction *b = numStack + (--numNum);
                                printf("b = %lld/%lld\n", b->numerator, b->denominator);
                                Fraction *a = numStack + (--numNum);
                                printf("a = %lld/%lld\n", a->numerator, a->denominator);
                                Fraction c;

                                switch (operStack[--operNum]) {
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

                                numStack[numNum++] = c;
                                printf("%lld/%lld\n", c.numerator, c.denominator);
                            }

                            operStack[operNum++] = oper;
                        } else {
                            operStack[operNum++] = oper;
                        }
                    } else {
                        operStack[operNum++] = oper;
                    }
                    break;
            }
        }
    }

    while (operStack[operNum - 1] != '(' && operNum) {

        checkNumStack();
        Fraction *b = numStack + (--numNum);
        printf("b = %lld/%lld\n", b->numerator, b->denominator);
        Fraction *a = numStack + (--numNum);
        printf("a = %lld/%lld\n", a->numerator, a->denominator);
        Fraction c;

        switch (operStack[--operNum]) {
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

        numStack[numNum++] = c;
        printf("%lld/%lld\n", c.numerator, c.denominator);
    }

    while (numNum) {
        Fraction result = numStack[--numNum];
        printf("%lld", result.numerator);
        if (result.denominator == 1) {
            putchar('\n');
        } else {
            printf("%lld\n", result.denominator);
        }
    }

    while (operNum) {
        printf("%c\n", operStack[--operNum]);
    }

    freeAllTokenNodes(infix);

    return 1;
}
