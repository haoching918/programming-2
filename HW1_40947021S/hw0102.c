#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define intt int32_t

intt main()
{
	printf("Please enter the original text:");
	char text[1025] = {'\0'};
	fgets(text, 1025, stdin);
	text[strlen(text) - 1] = '\0';

	printf("Keyword:\n");
	char keyword[129] = {'\0'};
	fgets(keyword, 129, stdin);
	keyword[strlen(keyword) - 1] = '\0';

	printf("New Word\n");
	char newWord[129] = {'\0'};
	fgets(newWord, 129, stdin);
	newWord[strlen(newWord) - 1] = '\0';

	printf("Before\n");
	intt record = 0;
	for (intt i = 0; i < strlen(text); i++)
	{
		if (i == (strstr(text + record, keyword) - text))
		{
			for (intt j = 0; j < strlen(keyword); j++)
			{
				printf("\033[34m%c\033[m", keyword[j]);
			}
			record += strlen(keyword) + i;
			i += strlen(keyword) - 1;
		}
		else
		{
			printf("%c", text[i]);
		}
	}
	printf("\nAfter:\n");
	record = 0;
	for (intt i = 0; i < strlen(text); i++)
	{
		if (i == (strstr(text + record, keyword) - text))
		{
			for (intt j = 0; j < strlen(newWord); j++)
			{
				printf("\033[31m%c\033[m", newWord[j]);
			}
			record += strlen(keyword) + i;
			i += strlen(keyword) - 1;
		}
		else
		{
			printf("%c", text[i]);
		}
	}
	printf("\n");

	return 0;
}