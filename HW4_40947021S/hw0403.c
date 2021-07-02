#include <stdio.h>
#include <stdint.h>
#include "myprintf.h"

int32_t main()
{
    myprintf("num : %d, hex : %X, str : %s \n", 123, 123, "Hello World");
    return 0;
}