#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse(const char *expr, char (*tokens)[maxExprLen])
{
    size_t len = strlen(expr);

    char *noOperExpr = malloc(sizeof(char) * (len + 1));
    memset(noOperExpr, 0, sizeof(char) * (len + 1));
    strcpy(noOperExpr, expr);

    for (size_t i = 0; i != len; ++i) {
        switch (noOperExpr[i]) {
            case '+': case '-':
            case '*': case '/': case '%':
            case '^':
            case '(': case ')':
                noOperExpr[i] = ' ';
                break;
            default:
                break;
        }
    }

    int tokenIndex = 0;
    for (size_t i = 0; i != len; ++i) {
        if (noOperExpr[i] == ' ') {
            char operToken[2] = {expr[i], '\0'};
            strcpy(tokens[tokenIndex++], operToken);
        } else {
            char numberToken[len + 1];
            memset(numberToken, 0, sizeof(numberToken));
            sscanf(noOperExpr + i, "%s", numberToken);
            strcpy(tokens[tokenIndex++], numberToken);
            while (noOperExpr[i] != ' ' && noOperExpr[i] != '\0') {
                ++i;
            }
            --i;
        }
    }

    free(noOperExpr);

    return 1;
}
