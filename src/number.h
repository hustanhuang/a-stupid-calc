#ifndef NUMBER_H_
#define NUMBER_H_

typedef char* baseNumber;

struct resultnumber {
    baseNumber numerator;
    baseNumber denominator;
};

typedef struct resultnumber resultNumber;

baseNumber createBaseNumber();

void createResultNumber(resultNumber *newNumber);
void freeResultNumber();

baseNumber strtonum(char *numstr);

baseNumber baseAdd(baseNumber a, baseNumber b);
baseNumber baseSub(baseNumber a, baseNumber b);
baseNumber baseMult(baseNumber a, baseNumber b);
baseNumber baseDiv(baseNumber a, baseNumber b);

#endif
