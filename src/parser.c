#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define errorSymbol(c) fprintf(stderr, "Illegal symbol: %c\n", c)

int parse(const char *expr, char (*tokens)[maxExprLen])
{
    size_t len = strlen(expr);

    //make a copy of the expr
    char noOperExpr[maxExprLen];
    memset(noOperExpr, 0, sizeof(maxExprLen));
    strcpy(noOperExpr, expr);

    //use a flag to ensure the +, - after the P, p, E, e are not seperated
    int previsEP = 0;

    //replace the operators in the noOperExpr with spaces
    for (size_t i = 0; i != len; ++i) {

        //use a pointer to simplify the code
        //dion't declare it in the for(...)
        //because c must be synchronized with i
        char *c = noOperExpr + i;

        //the legality of a number is checked when processing the tokens
        //xdigits, X, x and . are treated as part of a number
        if (isxdigit(*c) || *c == '.' || *c == 'x' || *c == 'X') {

            previsEP = 0;

        //P, p, E, e indicates the start of a exponential expression
        } else if (*c == 'P' || *c == 'p' || *c == 'E' || *c == 'e') {

            previsEP = 1;

        //processing the operators and the illegal symbols
        } else {

            switch (*c) {

                case '+': case '-': 
                    if (!previsEP) {
                        *c = ' ';
                    }
                    break;

                case '*': case '/': case '^':
                    *c = ' ';
                    break;

                case '(': case ')':
                    *c = ' ';
                    break;

                default:
                    errorSymbol(*c);
                    return 0;
            }

            previsEP = 0;
        }
    }

    //slice the tokens
    //the numbers are seperated with spaces in the noOperExpr
    //while the operators are at the corresponding palces in the expr
    int tokenIndex = 0;
    for (size_t i = 0; i != len; ++i) {

        //use a temp array to construct a string
        char tempToken[len + 1];
        memset(tempToken, 0, sizeof(tempToken));

        //if the present character is a space then
        //the corresponding character in the expr
        //is an operator
        if (noOperExpr[i] == ' ') {

            tempToken[0] = expr[i];
            strcpy(tokens[tokenIndex++], tempToken);

            //else it is a part of a number
        } else {

            sscanf(noOperExpr + i, "%s", tempToken);
            strcpy(tokens[tokenIndex++], tempToken);

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
