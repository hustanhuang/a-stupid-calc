#include "numStack.h"

#include <stdio.h>

long long gcd(long long a, long long b)
{
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    long long c = 1;
    while (a != b) {
        c = (a > b ? a - b : b - a);
        a = b;
        b = c;
    }
    return a;
}

void reduce(Fraction *thisFraction)
{
    long long divisor = gcd(thisFraction->numerator, thisFraction->denominator);
    thisFraction->numerator /= divisor;
    thisFraction->denominator /= divisor;
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
