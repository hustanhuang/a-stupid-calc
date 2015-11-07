#ifndef NUMBER_H_
#define NUMBER_H_

#include "defines.h"

struct basenumber {
    int sign;
    char xdigits[maxExprLen];
    int len;
};

typedef struct basenumber baseNumber;

void removeZero(baseNumber *number);
baseNumber createBaseNum(char *numstr);
void printBaseNum(const baseNumber *number);

#endif
