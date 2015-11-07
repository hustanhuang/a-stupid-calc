#include "operStack.h"

#include <stdlib.h>

int operPriority[256];

void initOperPriority()
{
    operPriority['+'] = 1;
    operPriority['-'] = 1;
    operPriority['*'] = 2;
    operPriority['/'] = 2;
    return;
}

char operStack[maxExprLen];
int operNum = 0;
