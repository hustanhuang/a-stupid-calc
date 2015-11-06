#include "number.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"

baseNumber createBaseNumber()
{
    baseNumber newNumber = malloc(sizeof(char) * maxExprLen);
    memset(newNumber, 0, sizeof(char) * maxExprLen);
    return newNumber;
}

void createResultNumber(resultNumber *newNumber)
{
    newNumber->numerator = createBaseNumber();
    newNumber->denominator = createBaseNumber();
    return;
}

void freeResultNumber(resultNumber *thisNumber)
{
    free(thisNumber->numerator);
    free(thisNumber->denominator);
    return;
}

void shrinkBaseBin(const baseNumber number)
{   
    int powof2[4] = { 1, 2, 4, 8 };
    int steps = strlen(number) / 4;

    baseNumber iter = number;
    for (int i = 0; i != steps; ++i) {

        int thisval = 0;

        for (int j = 0; j != 4; ++j) {
            if (*(iter + j) == '1') {
                thisval += powof2[3 - j];
            }
            *(iter + j) = '\0';
        }

        if (thisval < 10) {
            *(number + i) = '0' + thisval;
        } else {
            *(number + i) = 'A' + thisval - 10;
        }

        iter += 4;
    }

    return;
}

void shrinkBaseOct(const baseNumber number)
{   
    int powof8[4] = { 1, 8, 64, 512 };
    int powof16[3] = { 1, 16, 256 };
    int steps = strlen(number) / 3;

    baseNumber iter = number;
    for (int i = 0; i != steps; ++i) {

        int thisval = 0;

        for (int j = 0; j != 4; ++j) {
            thisval += (*(iter + j) - '0') * powof8[3 - j];
            *(iter + j) = '\0';
        }

        for (int j = 0; j != 3; ++j) {
            int subval = thisval / powof16[2 - j];
            if (subval < 10) {
                *(number + i + j) = '0' + subval;
            } else {
                *(number + i + j) = 'A' + subval - 10;
            }
            thisval %= powof16[2 - j];
        }

        iter += 4;
    }

    return;
}

baseNumber strtonum(char *numstr)
{
    baseNumber result = createBaseNumber();
    size_t numlen = strlen(numstr);

    if (numlen == 1) {
        numstr[0] = toupper(numstr[0]);
        strcpy(result, numstr);
        printf("is hex %s\n", result);
    } else if (*numstr == '1') {
        int placeHolderNum = 4 - numlen % 4;
        placeHolderNum = (placeHolderNum == 4) ? 0 : placeHolderNum;
        for (int i = 0; i != placeHolderNum; ++i) {
            result[i] = '0';
        }
        strcpy(result + placeHolderNum, numstr);
        printf("is bin %s\n", result);
        shrinkBaseBin(result);
    } else if (*numstr == '0') {
        if (toupper(*(numstr + 1)) == 'X') {
            for (int i = 0; i != strlen(numstr); ++i) {
                numstr[i] = toupper(numstr[i]);
            }
            strcpy(result, numstr + 2);
            printf("is hex %s\n", result);
        } else {
            int placeHolderNum = 4 - (numlen - 1) % 4;
            placeHolderNum = (placeHolderNum == 4) ? 0 : placeHolderNum;
            for (int i = 0; i != placeHolderNum; ++i) {
                result[i] = '0';
            }
            strcpy(result + placeHolderNum, numstr + 1);
            printf("is oct %s\n", result);
            shrinkBaseOct(result);
        }
    }
    return result;
}

/*baseNumber baseAdd(baseNumber a, baseNumber b);*/
/*baseNumber baseSub(baseNumber a, baseNumber b);*/
/*basenumber baseMult(baseNumber a, baseNumber b);*/
/*baseNumber baseDiv(baseNumber a, baseNumber b);*/
