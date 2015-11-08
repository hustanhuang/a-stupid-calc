#include "numStack.h"

intmax_t createNumber(const char *str, char **endptr) {
    return strtoimax(str, endptr, 0);
}

Fraction createFraction(intmax_t numerator, intmax_t denominator)
{
    Fraction newFraction = { numerator, denominator };
    return newFraction;
}

Fraction numStack[maxExprLen];
int numNum;

intmax_t gcd(intmax_t a, intmax_t b)
{
    //ensure that the gcd is a positive number
    if (a < 0) { a = -a; }
    if (b < 0) { b = -b; }

    intmax_t c = 1;
    while (a != b) {
        c = (a > b ? a - b : b - a);
        a = b;
        b = c;
    }

    return a;
}

void reduce(Fraction *thisFraction)
{
    intmax_t divisor = gcd(thisFraction->numerator, thisFraction->denominator);

    if (divisor == 0) {
        return;
    }

    if (divisor != 1) {
        thisFraction->numerator /= divisor;
        thisFraction->denominator /= divisor;
    }

    if (thisFraction->numerator < 0 && thisFraction->denominator < 0) {
        thisFraction->numerator *= -1;
        thisFraction->denominator *= -1;
    }

    if (thisFraction->denominator == -1) {
        thisFraction->denominator = 1;
        thisFraction->numerator *= -1;
    }
    return;
}
