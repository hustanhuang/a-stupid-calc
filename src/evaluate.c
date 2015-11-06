#include "evaluate.h"

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "tokens.h"
#include "parser.h"
#include "number.h"

int evaluate(const char *expr)
{
    tokenNode *infix = createTokenNode();
    addAfterTokenNode(infix);

    if (!parse(expr, infix)) {
        fprintf(stderr, "Parsing failed\n");
        return 0;
    }

    for (tokenNode *i = infix->next; i->token != NULL; i = i->next) {
        printf("%s ", i->token);
    }
    putchar('\n');

    char a[128];
    scanf("%s", a);
    baseNumber b = strtonum(a);
    printf("0X%s\n", b);

    freeAllTokenNodes(infix);

    return 1;
}
