#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"

#define errorSymbol(c) fprintf(stderr, "Illegal symbol: %c\n", c)

int parse(const char *expr, tokenNode *infix)
{
    size_t len = strlen(expr);

    //make a copy of the expr
    char noOperExpr[maxExprLen];
    memset(noOperExpr, 0, sizeof(noOperExpr));
    strcpy(noOperExpr, expr);

    //replace the operators in the noOperExpr with spaces
    for (size_t i = 0; i != len; ++i) {

        //use a pointer to simplify the code
        char *c = noOperExpr + i;

        //xdigits, X & x are treated as part of a number
        if (!isxdigit(*c) && toupper(*c) != 'X') {

            //processing the operators and the illegal symbols
            switch (*c) {

                case '_':
                case '+': case '-': 
                case '*': case '/':
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
    for (size_t i = 0; i != len; ++i) {

        //use a temp array to construct a string
        char *tempToken = malloc(sizeof(char) * (len + 1));
        memset(tempToken, 0, sizeof(char) * (len + 1));

        if (noOperExpr[i] == ' ') {

            *tempToken = expr[i];
            infix = addAfterTokenNode(infix);
            infix->token = tempToken;

        } else {

            sscanf(noOperExpr + i, "%s", tempToken);

            //ensure all characters are capital
            for (size_t j = 0; j != strlen(tempToken); ++j) {
                tempToken[j] = toupper(tempToken[j]);
            }

            infix = addAfterTokenNode(infix);
            infix->token = tempToken;

            //move i to the place where the next operator occurs
            //or to the end of the string
            while (noOperExpr[i] != ' ' && noOperExpr[i] != '\0') {
                ++i;
            }

            //correct the place of i
            --i;
        }
    }

    return 1;
}
