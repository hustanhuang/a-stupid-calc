#include "numberCalc.h"

int baseAbsComp(const baseNumber *a, const baseNumber *b)
{
    if (a->len == b->len) {
        for (int i = 0; i != a->len; ++i) {
            if (a->xdigits[i] > b->xdigits[i]) {
                return 1;
            } else if (a->xdigits[i] < b->xdigits[i]) {
                return -1;
            }
        }
        return 0;
    } else {
        if (a->len > b->len) {
            return 1;
        } else {
            return -1;
        }
    }
}

baseNumber baseAdd(const baseNumber *a, const baseNumber *b)
{
    if (a->sign == 0) {
        return *b;
    }

    if (b->sign == 0) {
        return *a;
    }

    baseNumber result;
    int comp = baseAbsComp(a, b);

    if (a->sign == b->sign) {

        result = baseDoAdd(a, b);
        result.sign = a->sign;
        return result;

    } else {

        if (comp == 1) {

            result = baseDoSub(a, b);
            result.sign = a->sign;
            return result;

        } else if (comp == -1) {

            result = baseDoSub(b, a);
            result.sign = b->sign;
            return result;

        } else {

            result = createBaseNum("0");
            return result;
        }
    }
}

baseNumber baseSub(const baseNumber *a, const baseNumber *b)
{
    if (a->sign == 0) {
        baseNumber c = *b;
        c.sign *= -1;
        return c;
    }

    if (b->sign == 0) {
        return *a;
    }

    baseNumber result;
    int comp = baseAbsComp(a, b);

    if (a->sign != b->sign) {

        result = baseDoAdd(a, b);
        result.sign = a->sign;
        return result;

    } else {

        if (comp == 1) {

            result = baseDoSub(a, b);
            result.sign = a->sign;
            return result;

        } else if (comp == -1) {

            result = baseDoSub(b, a);
            result.sign = (-1) * b->sign;
            return result;

        } else {

            result = createBaseNum("0");
            return result;
        }
    }
}

baseNumber baseDoAdd(const baseNumber *a, const baseNumber *b)
{
    baseNumber result = createBaseNum("0");
    const baseNumber *longer = (a->len > b->len ? a : b);
    const baseNumber *shorter = (a->len < b->len ? a : b);
    int longLen = longer->len;
    int shortLen = shorter->len;
    result.len = longLen + 1;

    char *thisDigit = result.xdigits + result.len - 1;
    for (int i = 0; i != shortLen; ++i) {
        *thisDigit += a->xdigits[a->len - 1 - i] + b->xdigits[b->len - 1 - i];
        thisDigit[-1] += *thisDigit / 16;
        *thisDigit %= 16;
        --thisDigit;
    }

    for (int i = shortLen; i != longLen; ++i) {
        *thisDigit += longer->xdigits[longLen - 1 - i];
        thisDigit[-1] += *thisDigit / 16;
        *thisDigit %= 16;
        --thisDigit;
    }

    removeZero(&result);
    return result;
}

baseNumber baseDoSub(const baseNumber *a, const baseNumber *b)
{
    baseNumber result = createBaseNum("0");
    int longLen = a->len;
    int shortLen = b->len;
    result.len = longLen + 1;

    char *thisDigit = result.xdigits + result.len - 1;
    for (int i = 0; i != shortLen; ++i) {
        *thisDigit += a->xdigits[a->len - 1 - i] - b->xdigits[b->len - 1 - i];
        thisDigit[-1] += *thisDigit / 16;
        *thisDigit %= 16;
        if (*thisDigit < 0) {
            thisDigit[-1] -= 1;
            *thisDigit += 16;
        }
        --thisDigit;
    }

    for (int i = shortLen; i != longLen; ++i) {
        *thisDigit += a->xdigits[longLen - 1 - i];
        thisDigit[-1] += *thisDigit / 16;
        *thisDigit %= 16;
        if (*thisDigit < 0) {
            thisDigit[-1] -= 1;
            *thisDigit += 16;
        }
        --thisDigit;
    }

    removeZero(&result);
    return result;
}
