#ifndef NUMSTACK_H_
#define NUMSTACK_H_

struct fraction {
    long long numerator;
    long long denominator;
};

typedef struct fraction Fraction;

long long gcd(long long a, long long b);
void reduce(Fraction *thisFraction);

#endif
