#include "evaluate.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"
#include "tokens.h"
#include "parser.h"
#include "number.h"
#include "numberCalc.h"

int evaluate(const char *expr)
{
    /*tokenNode *infix = createTokenNode();*/
    /*addAfterTokenNode(infix);*/

    /*if (!parse(expr, infix)) {*/
        /*fprintf(stderr, "Parsing failed\n");*/
        /*return 0;*/
    /*}*/

    /*for (tokenNode *i = infix->next; i->token != NULL; i = i->next) {*/
        /*printf("%s ", i->token);*/
    /*}*/
    /*putchar('\n');*/

    char as[128], bs[128];
    scanf("%s", as);
    scanf("%s", bs);

    for (int i = 0; as[i]; ++i) {
        as[i] = toupper(as[i]);
    }

    for (int i = 0; bs[i]; ++i) {
        bs[i] = toupper(bs[i]);
    }

    baseNumber a = createBaseNum(as);
    baseNumber b = createBaseNum(bs);

    baseNumber c = createBaseNum("0");

    /*printf("a = (%d) ", a.sign);*/
    /*printBaseNum(&a);*/
    /*putchar('\n');*/

    /*printf("b = (%d) ", b.sign);*/
    /*printBaseNum(&b);*/
    /*putchar('\n');*/

    printf("a comp b? %d\n", baseAbsComp(&a, &b));

    c = baseAdd(&a, &b);

    printf("c = ");
    printBaseNum(&c);
    putchar('\n');
    /*for (int i = 0; i != 128; ++ i) {*/
        /*printf("%d ", c.xdigits[i]);*/
    /*}*/
    /*putchar('\n');*/

    c = baseSub(&a, &b);

    printf("c = ");
    printBaseNum(&c);
    putchar('\n');
    /*for (int i = 0; i != 128; ++ i) {*/
        /*printf("%d ", c.xdigits[i]);*/
    /*}*/
    /*putchar('\n');*/

    /*c = baseMult(a, b);*/

    /*printf("c = ");*/
    /*printBaseNum(&b);*/
    /*putchar('\n');*/

    /*c = baseMod(a, b);*/

    /*printf("c = ");*/
    /*printBaseNum(&b);*/
    /*putchar('\n');*/

    /*freeAllTokenNodes(infix);*/

    return 1;
}
