#ifndef NUMSTACK_H_
#define NUMSTACK_H_

#include <inttypes.h>
#include "defines.h"

struct fraction {
    intmax_t numerator;
    intmax_t denominator;
};

typedef struct fraction Fraction;

intmax_t createNumber(const char *str, char **endptr);
Fraction createFraction();

extern Fraction numStack[maxExprLen];
extern int numNum;

#define pushNum(n) (numStack[numNum++] = n)
#define popNum() (numStack + (--numNum))
#define getTopNum() (numStack + numNum - 1)

intmax_t gcd(intmax_t a, intmax_t b);

void reduce(Fraction *thisFraction);

#endif
