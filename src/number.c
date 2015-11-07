#include "number.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"

void shrinkBaseBin(baseNumber *number)
{   
    //2^4 == 16^1
    int powof2[4] = { 1, 2, 4, 8 };

    int sectionNum = strlen(number->xdigits) / 4;
    number->len = sectionNum;

    char *iter = number->xdigits;
    for (int i = 0; i != sectionNum; ++i) {

        //get the value of each section
        int sectionVal = 0;
        for (int j = 0; j != 4; ++j) {
            sectionVal += (iter[j] - '0') * powof2[3 - j];
            iter[j] = '\0';
        }

        //set the value of this section
        number->xdigits[i] = sectionVal;

        //go to next section
        iter += 4;
    }

    return;
}

void shrinkBaseOct(baseNumber *number)
{   
    //8^4 == 16^3
    int powof8[4] = { 1, 8, 64, 512 };
    int powof16[3] = { 1, 16, 256 };

    int sectionNum = strlen(number->xdigits) / 4;
    const int segmentNum = 3;
    number->len = sectionNum * 3;

    char *iter = number->xdigits;
    for (int i = 0; i != sectionNum; ++i) {

        //get the value of each section
        int sectionVal = 0;
        for (int j = 0; j != 4; ++j) {
            sectionVal += (iter[j] - '0') * powof8[3 - j];
            iter[j] = '\0';
        }

        //cut the section
        for (int j = 0; j != segmentNum; ++j) {

            //set the value of this segment
            number->xdigits[i * segmentNum + j] = sectionVal / powof16[2 - j];

            //go to next segment
            sectionVal %= powof16[2 - j];
        }

        //go to next section
        iter += 4;
    }

    return;
}

void shrinkBaseHex(baseNumber *number)
{
    char *iter = number->xdigits;
    number->len = strlen(number->xdigits);

    while (*iter) {
        if (isdigit(*iter)) {
            *iter -= '0';
        } else {
            *iter = *iter - 'A' + 10;
        }
        iter++;
    }

    return;
}

void removeZero(baseNumber *number)
{
    if (number->len != 1) {
        int zeroNum = 0;
        for (int i = 0; !number->xdigits[i] && i != number->len; ++i) {
            ++zeroNum;
        }
        if (zeroNum) {
            for (int i = 0; i != number->len - zeroNum; ++i) {
                number->xdigits[i] = number->xdigits[i + zeroNum];
                number->xdigits[i + zeroNum] = 0;
            }
        }
        number->len -= zeroNum;
    }
    return;
}

baseNumber createBaseNum(char *numstr)
{
    baseNumber result;
    memset(&result, 0, sizeof(result));
    result.sign = 1;
    size_t numlen = strlen(numstr);

    //bin
    if (*numstr == '1') {

        int placeHolderNum = 4 - numlen % 4;
        placeHolderNum = (placeHolderNum == 4) ? 0 : placeHolderNum;
        for (int i = 0; i != placeHolderNum; ++i) {
            result.xdigits[i] = '0';
        }

        strcpy(result.xdigits + placeHolderNum, numstr);
        shrinkBaseBin(&result);

    } else if (*numstr == '0') {

        //single 0
        if (!numstr[1]) {

            result.sign = 0;
            result.len = 1;

        //hex
        } else if (numstr[1] == 'X') {

            strcpy(result.xdigits, numstr + 2);
            shrinkBaseHex(&result);

        //oct
        } else if (isdigit(numstr[1])) {

            int placeHolderNum = 4 - (numlen - 1) % 4;
            placeHolderNum = (placeHolderNum == 4) ? 0 : placeHolderNum;
            for (int i = 0; i != placeHolderNum; ++i) {
                result.xdigits[i] = '0';
            }

            strcpy(result.xdigits + placeHolderNum, numstr + 1);
            shrinkBaseOct(&result);
        } 
    }

    removeZero(&result);

    return result;
}

void printBaseNum(const baseNumber *number)
{
    if (number->sign == -1) {
        putchar('-');
    } else if (number->sign == 0) {
        putchar('0');
    }
    for (int i = 0; i != number->len; ++i) {
        if (number->xdigits[i] > 9) {
            putchar(number->xdigits[i] - 10 + 'A');
        } else {
            putchar(number->xdigits[i] + '0');
        }
    }
    return;
}
