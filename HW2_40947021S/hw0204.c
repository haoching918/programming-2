#include <stdio.h>
#include <stdint.h>
#include "bignum.h"

int main()
{
	sBigNum a, b;
	set(&a, "123");
	set(&b, "-999");
	print(a);
	print(b);
	if (compare(a, b) == 1)
	{
		printf("ComparisonPass.\n");
	}
	else
	{
		printf("ComparisonFail.\n");
	}
	if (digits(a) == 3)
	{
		printf("DigitsPass.\n");
	}
	else
	{
		printf("DigitsFail.\n");
	}
	sBigNum ans, q, r;
	add(&ans, a, b);
	print(ans);
	subtract(&ans, a, b);
	print(ans);
	multiply(&ans, a, b);
	print(ans);
	divide(&q, &r, a, b);
	print(q);
	print(r);
	power(&ans, 20, 10);
}