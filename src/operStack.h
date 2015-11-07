#ifndef OPERSTACK_H_
#define OPERSTACK_H_

#include "defines.h"

extern int operPriority[256];

void initOperPriority();

extern char operStack[maxExprLen];
extern int operNum;

#define pushOper(c) operStack[operNum++] = c

#define popOper() operStack[--operNum]

#define getTopOper() operStack[operNum - 1]

#endif
