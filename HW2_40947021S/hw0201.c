#include"mixed.h"

int32_t main()
{
    sMixedNumber r1;
    sMixedNumber r2;
    sMixedNumber result;

    mixed_set(&r1, 2, 3, 4);
    mixed_set(&r2, 3, 0, 0);

    mixed_print(r1);
    mixed_print(r2);

    mixed_add(&result, r1, r2);
    mixed_print(result);

    mixed_sub(&result, r1, r2);
    mixed_print(result);

    mixed_mul(&result, r1, r2);
    mixed_print(result);

    mixed_div(&result, r1, r2);
    mixed_print(result);
    return 0;
}