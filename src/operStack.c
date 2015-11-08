#include "operStack.h"

int operPriority[256];

void initOperPriority()
{
    operPriority['+'] = 1;
    operPriority['-'] = 1;
    operPriority['*'] = 2;
    operPriority['/'] = 2;
    operPriority['P'] = 3;
    operPriority['N'] = 3;
    return;
}

char operStack[maxExprLen];
int operNum = 0;
