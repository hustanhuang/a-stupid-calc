#include "evaluate.h"

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "parser.h"
#include "convert.h"

char tokens[maxExprLen][maxExprLen];
char postfix[maxExprLen][maxExprLen];

int evaluate(const char *expr)
{
    memset(tokens, 0, sizeof(tokens));
    memset(postfix, 0, sizeof(postfix));

    if (!parse(expr, tokens)) {
        fprintf(stderr, "Parsing failed\n");
        return 0;
    }

    for (size_t i = 0; i != maxExprLen; ++i) {
        if (tokens[i][0]) {
            printf("%s ", tokens[i]);
        }
    }
    putchar('\n');

    if (!convert(tokens, postfix)) {
        fprintf(stderr, "Convertion failed\n");
        return 0;
    }

    for (size_t i = 0; i != maxExprLen; ++i) {
        if (postfix[i][0]) {
            printf("%s ", postfix[i]);
        }
    }
    putchar('\n');

    return 1;
}
