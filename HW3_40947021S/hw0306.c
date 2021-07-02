#include <stdio.h>
#include <stdint.h>

void max(int32_t a,int32_t b)
{
    printf("%d\n",(a & (-(a>=b))) + (b & (-(b>a))));
}

int main()
{
    int32_t a = 4;
    int32_t b = 4;

    max(a,b);

    return 0;
}