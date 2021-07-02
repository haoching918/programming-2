#include "stdio.h"
#include "stdint.h"
#include "math.h"
#define int int32_t

typedef union
{
	struct
	{
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
		unsigned char b8 : 1;
	} bits;
	unsigned char byte;
} uByte;

int main()
{
	uByte input;
	int binInput[8] = {0};
	int data = 0;
	printf("Please enter a byte (0-255): ");
	if(scanf("%d", &data) != 1 || data < 0 || data > 255)
	{
		printf("Invalid input\n");
		return -1;
	}
	input.byte = data;
	int tmp = input.byte;
	for (int i = 7; i >= 0; i--)
	{
		binInput[i] = tmp % 2;
		tmp /= 2;
	}
	while (1)
	{
		int choice = 0;
		input.bits.b1 = binInput[0];
		input.bits.b2 = binInput[1];
		input.bits.b3 = binInput[2];
		input.bits.b4 = binInput[3];
		input.bits.b5 = binInput[4];
		input.bits.b6 = binInput[5];
		input.bits.b7 = binInput[6];
		input.bits.b8 = binInput[7];
		input.byte = input.bits.b1*pow(2,7)+input.bits.b2*pow(2,6)
		+input.bits.b3*pow(2,5)+input.bits.b4*pow(2,4)+input.bits.b5*pow(2,3)
		+input.bits.b6*pow(2,2)+input.bits.b7*pow(2,1)+input.bits.b8*pow(2,0);
		printf("Data: %hhu ", input.byte);
		for (int i = 0; i < 8; i++)
			printf("%d", binInput[i]);
		printf("\nFlip bit (1-8, 0: exit): ");
		if(scanf("%d", &choice) != 1 || choice < 1 || choice > 8)
		{
			printf("Invalid input\n");
			return -1;
		}
		if (choice == 0)
		{
			printf("bye\n");
			return 0;
		}
		else
		{
			if (binInput[choice - 1] == 1)
				binInput[choice - 1] = 0;
			else
				binInput[choice - 1] = 1;
		}
	}
	return 0;
}