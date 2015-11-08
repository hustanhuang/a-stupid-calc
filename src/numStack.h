#ifndef NUMSTACK_H_
#define NUMSTACK_H_

#include "defines.h"

struct fraction {
    long long numerator;
    long long denominator;
};

typedef struct fraction Fraction;

Fraction createFraction();

extern Fraction numStack[maxExprLen];
extern int numNum;

#define pushNum(n) (numStack[numNum++] = n)
#define popNum() (numStack + (--numNum))
#define getTopNum() (numStack + numNum - 1)

long long gcd(long long a, long long b);

void reduce(Fraction *thisFraction);

#endif
