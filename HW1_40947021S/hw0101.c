#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define intt int32_t

intt main()
{
	printf("Please enter the hex string:");

	char inputStr[100];
	fgets(inputStr, 100, stdin);
	inputStr[strlen(inputStr) - 1] = '\0';
	for (intt i = 0; i < 100; i++)
	{
		if (i % 2 == 0 && inputStr[i] == '0' && inputStr[i + 1] == '0')
		{
			if (inputStr[i + 2] != '\0')
			{
				printf("error\n");
				return 0;
			}
			break;
		}
		if (!isxdigit(inputStr[i]))
		{
			printf("error\n");
			return 0;
		}
	}

	for (intt i = 0; i < 100; i += 2)
	{
		if (inputStr[i] == '0' && inputStr[i + 1] == '0')
		{
			break;
		}
		char str[3] = {inputStr[i], inputStr[i + 1]};
		char **ptr;
		int hex = strtol(str, ptr, 16);
		printf("%c", hex);
	}
	printf("\n");
	return 0;
}