#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_COLOR_RESET "\x1b[0m"

void changeCol(int c)
{
	switch (c)
	{
	case 1:
		printf(ANSI_COLOR_RED);
		break;
	case 2:
		printf(ANSI_COLOR_GREEN);
		break;
	case 3:
		printf(ANSI_COLOR_BLUE);
		break;
	case 4:
		printf(ANSI_COLOR_MAGENTA);
		break;
	case 5:
		printf(ANSI_COLOR_CYAN);
		break;
	case 6:
		printf(ANSI_COLOR_YELLOW);
		break;
	case 0:
		printf(ANSI_COLOR_WHITE);
		break;
	default:
		break;
	}
}

int32_t main()
{
	char filename[50] = {0};
	FILE *pFile = NULL;
	printf("Open a LRC file: ");
	fgets(filename, 50, stdin);
	if (filename[strlen(filename) - 1] == '\n')
		filename[strlen(filename) - 1] = '\0';
	if ((pFile = fopen(filename, "r")) == NULL)
	{
		perror("Error: ");
		return 1;
	}

	double preTime = 0.0;
	double curTime = 0.0;
	char lrcStr[100] = {'\0'};
	int32_t color[10] = {0};
	int32_t colIndex = 0;
	int32_t charIndex = 0;

	char **charactor = NULL;
	charactor = calloc(sizeof(int64_t), 10); //人名陣列 前者為pointer大小後者為腳色數量
	for (int32_t i = 0; i < 10; i++)
		*(charactor + i) = calloc(sizeof(charactor), 20);

	while (!feof(pFile))
	{
		int32_t repeat = -1;

		fgets(lrcStr, 100, pFile);
		lrcStr[strlen(lrcStr) - 1] = '\0';

		if (lrcStr[0] != '[' && lrcStr[strlen(lrcStr) - 2] == ':') // 取得人名
		{
			printf(ANSI_COLOR_RESET);
			lrcStr[strlen(lrcStr) - 1] = '\0';
			for (size_t i = 0; i < charIndex; i++)
			{
				if (!strcmp(lrcStr, *(charactor + i)))
				{
					repeat = i;
					break;
				}
			}
			if (repeat == -1) //如果人名未重複
			{
				strncpy(*(charactor + charIndex), lrcStr, 20);
				colIndex = charIndex;
				charIndex++;
			}
			else
			{
				colIndex = repeat; //colIndex對應腳色陣列
			}
			changeCol(colIndex);
		}
		else if (lrcStr[0] == '[' && lrcStr[1] >= '0' && lrcStr[1] <= '9')
		{
			char *str = lrcStr + 10;
			int min;
			double sec;
			sscanf(lrcStr, "[%d:%lf]", &min, &sec);

			double time = min * 60 + sec;
			usleep((time - preTime) * 1000000); //微秒單位
			preTime = time;
			printf("%s\n", str);
		}
	}
	fclose(pFile);
	return 0;
}
