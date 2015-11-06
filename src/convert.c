#include "convert.h"

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define addPostfix(token) strcpy(postfix[postfixNum++], token)

#define pushOper(oper) operStack[++operNum] = oper
#define popOper() operStack[operNum--]

int convert(const char (*infix)[maxExprLen], char (*postfix)[maxExprLen])
{
    //init the counters
    int infixNum = 0;
    int postfixNum = 0;
    int i = 0;

    //get the number of infix tokens
    for (i = 0; infix[i][0] && i != maxExprLen; ++i) {
        ; //do nothing
    }
    infixNum = i;

    //init the operator stack
    //the operStack[0] = '\0' is a sentinel
    char operStack[maxExprLen + 1];
    memset(operStack, 0, sizeof(operStack));
    int operNum = 0;

    //init the operator priority table
    int operPriority[256];
    memset(operPriority, -1, sizeof(operPriority));

    //set the priority
    operPriority['('] = INT_MAX;
    operPriority['^'] = 0;
    operPriority['*'] = 1;
    operPriority['/'] = 1;
    operPriority['+'] = 2;
    operPriority['-'] = 2;

    for (i = 0; i != infixNum; ++i) {

        //get the token
        const char *token = infix[i];

        //if the first character is a digit
        //or it's length is longer than 1
        //then it is a number
        if (isdigit(*token) || token[1]) {
            addPostfix(token);

        //processing the operators
        } else {
            
            //get the operator
            const char oper = *token;

            //a char to save the top operator
            char topOper = '\0';

            //'(' is simply pushed into the stack
            if (oper == '(') {
                pushOper(oper);

            //when encounter ')'
            } else if (oper == ')') {

                //loop poping the operators
                //until encounter a '('
                //or the stack is empty (ERROR)
                while (operNum && operStack[operNum] != '(') {

                    //convert the operator into a string and add it to postfixTokens
                    char operToken[2] = {popOper(), '\0'};
                    addPostfix(operToken);
                }

                //after poping the top element left should be a '('
                if (popOper() != '(') {
                    fprintf(stderr, "Parenthesises cannot match\n");
                    return 0;
                }

            //dealing with normal operators
            } else if ((topOper = operStack[operNum]) != '\0') {

                //use a var to store the value
                //in order to avoid getting wrong values
                //during forced type convert
                int operIndex = oper, topOperIndex = topOper;

                //if this operator is prior than the stack-top operator
                //simply push it into the stack
                if (operPriority[operIndex] <= operPriority[topOperIndex]) {
                    pushOper(oper);

                //otherwise pop all the operators
                //until encounter a '('
                //or the stackis empty
                } else {

                    while (operNum && operStack[operNum] != '(') {

                    //convert the operator into a string and add it to postfixTokens
                    char operToken[2] = {popOper(), '\0'};
                    addPostfix(operToken);
                    }

                    //then push this operator into the stack
                    pushOper(oper);
                }
            } else {

                //if the stack is empty
                //simply push it into the stack
                pushOper(oper);
            }
        }
    }

    while (operNum) {
        //convert the operator into a string and add it to postfixTokens
        char operToken[2] = {popOper(), '\0'};

        //there shouldn't be any '(' left
        if (operToken[0] == '(') {
            fprintf(stderr, "Parenthesises cannot match\n");
            return 0;
        }

        addPostfix(operToken);
    }

    return 1;
}
