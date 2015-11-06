#include "evaluate.h"

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "parser.h"

char tokens[maxExprLen][maxExprLen];

int evaluate(const char *expr)
{
    memset(tokens, 0, sizeof(tokens));

    parse(expr, tokens);

    for (size_t i = 0; i != maxExprLen; ++i) {
        if (strlen(tokens[i])) {
            printf("%s ", tokens[i]);
        }
    }
    putchar('\n');

    return 1;
}
