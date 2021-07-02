#include"hw0103.h"

void swap()
{
    char *tmp = pStr01;
    pStr01 = pStr02;
    pStr02 = tmp;
    return;
}

int main()
{
    swap();
    prinft_answers();
    return 0;
}