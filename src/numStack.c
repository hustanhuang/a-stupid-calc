#include "numStack.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int readNumErr = 0;

intmax_t createNumber(const char *str, char **endptr) {
    int base = 0;
    if (str[0] == '0') {
        switch (str[1]) {
            case '0':
                base = 2;
                break;

            case 'x': case 'X':
                base = 16;
                break;

            default:
                base = 8;
                break;
        }
    } else if (isalpha(str[0])) {
        if (*endptr != str && *endptr != str + strlen(str)) {
            fprintf(stderr, "Error number: %s\n", str);
            readNumErr = 1;
            return 0;
        }
    }

    intmax_t result = strtoimax(str, endptr, base);

    if (*endptr != str && *endptr != str + strlen(str)) {
        fprintf(stderr, "Error number: %s\n", str);
        readNumErr = 1;
        return 0;
    }
    return result;
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
