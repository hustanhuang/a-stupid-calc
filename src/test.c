#include <stdio.h>

#include "defines.h"
#include "number.h"
#include "numberCalc.h"

int main()
{
    char str[maxExprLen];
    scanf("%s", str);
    baseNumber a = createBaseNum(str);
    scanf("%s", str);
    baseNumber b = createBaseNum(str);

    baseNumber c = createBaseNum("0");

    printf("a = ");
    printBaseNum(&a);
    putchar('\n');

    printf("b = ");
    printBaseNum(&b);
    putchar('\n');

    printf("a comp b = %d\n", baseAbsComp(&a, &b));

    c = baseAdd(&a, &b);
    printBaseNum(&c);
    putchar('\n');

    c = baseSub(&a, &b);
    printBaseNum(&c);
    putchar('\n');

    c = baseMult(&a, &b);
    printBaseNum(&c);
    putchar('\n');

    /*c = baseAdd(&a, &b);*/
    /*printBaseNum(&c);*/
    /*putchar('\n');*/

    return 0;
}
