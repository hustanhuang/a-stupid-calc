#ifndef NUMBERCALC_H_
#define NUMBERCALC_H_

#include "number.h"

int baseAbsComp(const baseNumber *a, const baseNumber *b);

baseNumber baseAdd(const baseNumber *a, const baseNumber *b);
baseNumber baseSub(const baseNumber *a, const baseNumber *b);

baseNumber baseDoAdd(const baseNumber *a, const baseNumber *b);
baseNumber baseDoSub(const baseNumber *a, const baseNumber *b);

baseNumber baseMult(const baseNumber *a, const baseNumber *b);
baseNumber baseDiv(const baseNumber *a, const baseNumber *b);

#endif
