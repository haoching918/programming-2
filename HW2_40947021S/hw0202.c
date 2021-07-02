#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "math.h"
#define int int32_t

int main()
{
	double input = 0.0;
	printf("Please enter a floating-point number (double precision):");
	scanf("%lf", &input);
	if (input > 0)
		printf("Sign: 0\n");
	else
		printf("Sign: 1\n");
	printf("Exponent: ");
	int binInput[65] = {0};
	int n = abs((int)input);
	int i = 0;
	for (int j = abs(log2(n)); j >= 0; j--) //將整數部分填入binInput
	{
		int k = n >> j;
		if (k & 1)
			binInput[i] = 1;
		else
			binInput[i] = 0;
		i++;
	}
	int exponent = i - 1; //求偏移植
	int dotIndex = i;
	binInput[i] = 5;
	i++;
	double tmp = fabs(input) - abs((int)input);
	for (i; i < 65; i++) //將小數部分填入binInput
	{
		tmp *= 2;
		if (tmp >= 1)
		{
			binInput[i] = 1;
			tmp -= 1;
		}
		else
			binInput[i] = 0;
	}
	for (int c = 10; c >= 0; c--) //輸出 exponent + 1023 的 binary
	{
		int k = (exponent + 1023) >> c;;
		if (k & 1)
			printf("1");
		else
			printf("0");
	}
	printf("\nFraction: "); // fraction
	for (int j = 1; j <= 53; j++)
	{
		if (j == dotIndex)
			continue;
		printf("%d", binInput[j]);
	}
	printf("\n%lf = ", input); // 輸出等式
	if (input > 0)
		printf("(-1)^0 * ");
	else
		printf("(-1)^1 * ");
	printf("(");
	for (int j = 0; j < dotIndex; j++)
		if (binInput[j] == 1)
			printf("2^%d + ", dotIndex - j - 1);
	for (int j = dotIndex + 1; j < 53; j++)
		if (binInput[j] == 1)
			printf("2^%d + ", dotIndex - j);
	printf("\b\b\b) * 2^(%d-1023)\n", 1023 + exponent);
	return 0;
}
