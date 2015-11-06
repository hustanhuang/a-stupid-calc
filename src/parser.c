#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define errorSymbol(c) fprintf(stderr, "Illegal symbol: %c\n", c)

int parse(const char *expr, tokenNode *infix)
{
    size_t len = strlen(expr);

    //make a copy of the expr
    char noOperExpr[maxExprLen];
    memset(noOperExpr, 0, sizeof(maxExprLen));
    strcpy(noOperExpr, expr);

    //replace the operators in the noOperExpr with spaces
    for (size_t i = 0; i != len; ++i) {

        //use a pointer to simplify the code
        //dion't declare it in the for(...)
        //because c must be synchronized with i
        char *c = noOperExpr + i;

        //the legality of a number is checked when processing the tokens
        //xdigits, X & x are treated as part of a number
        if (!isxdigit(*c) && toupper(*c) != 'X') {

            //processing the operators and the illegal symbols
            switch (*c) {

                case '+': case '-': 
                case '*': case '/': case '%':
                case '(': case ')':
                    *c = ' ';
                    break;

                default:
                    errorSymbol(*c);
                    return 0;
            }
        }
    }

    //slice the tokens
    //the numbers are seperated with spaces in the noOperExpr
    //while the operators are at the corresponding palces in the expr
    for (size_t i = 0; i != len; ++i) {

        //use a temp array to construct a string
        char *tempToken = malloc(sizeof(char) * (len + 1));
        memset(tempToken, 0, sizeof(char) * (len + 1));

        //if the present character is a space then
        //the corresponding character in the expr
        //is an operator
        if (noOperExpr[i] == ' ') {

            *tempToken = expr[i];
            infix = addAfterTokenNode(infix);
            infix->token = tempToken;

            //else it is a part of a number
        } else {

            sscanf(noOperExpr + i, "%s", tempToken);
            infix = addAfterTokenNode(infix);
            infix->token = tempToken;

            //move i to the place
            //where the next operator occurs
            //or the end of the string
            while (noOperExpr[i] != ' ' && noOperExpr[i] != '\0') {
                ++i;
            }

            //correct the place of i
            --i;
        }
    }

    return 1;
}
