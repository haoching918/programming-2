#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct _sMixedNumber
{
    int32_t whole;
    int32_t numerator;
    int32_t denominator;
} sMixedNumber;

int32_t mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c);
int32_t GCD(int32_t a, int32_t b);
int32_t LCM(int32_t a, int32_t b);
int32_t mixed_print(const sMixedNumber number);
void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
