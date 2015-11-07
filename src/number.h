#ifndef NUMBER_H_
#define NUMBER_H_

#include "defines.h"

struct basenumber {
    int sign;
    char xdigits[maxExprLen];
    int len;
};

typedef struct basenumber baseNumber;

struct resultnumber {
    baseNumber numerator;
    baseNumber denominator;
};

typedef struct resultnumber resultNumber;

baseNumber createBaseNum(char *numstr);
void printBaseNum(const baseNumber *number);
void removeZero(baseNumber *number);

#endif
