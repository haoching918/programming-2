#include "function.h"

int32_t main()
{
	FILE *pFile = NULL;
	char filename[32] = {0};
	printf("Please open a season record: ");
	fgets(filename, 32, stdin);
	filename[strlen(filename) - 1] = '\0';
	if ((pFile = fopen(filename, "r")) == NULL)
	{
		perror("error");
		return 1;
	}

	teamInfo teamList[20];
	int32_t tListIndex = 0;
	game gameList[380];
	int32_t gListIndex = 0;

	char tmpBuf[100]; // 每行暫存資料
	fgets(tmpBuf, 100, pFile);
	while (!feof(pFile))
	{
		fgets(tmpBuf, 100, pFile);
		// game
		sscanf(tmpBuf, "%[^,],%[^,],%[^,],%d,%d", gameList[gListIndex].date, gameList[gListIndex].HT, gameList[gListIndex].AT, &gameList[gListIndex].HG, &gameList[gListIndex].AG);
		gameList[gListIndex].scoreGap = abs(gameList[gListIndex].HG - gameList[gListIndex].AG);
		gListIndex++;

		// team
		char tmpHTName[20] = {0};
		char tmpATName[20] = {0};

		sscanf(tmpBuf, "%*[^,],%[^,],%[^,]", tmpHTName, tmpATName);

		// 主場
		// tmp 資料
		int32_t repeat = -1;
		int32_t tscore;
		char FTR;
		int32_t tHr; // temporary Home team Redcard
		int32_t tAr; // temporary Away team Redcard
		int32_t tGA;
		sscanf(tmpBuf, "%*[^,],%*[^,],%*[^,],%d,%d,%c%*9s%*[^,],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%*[0-9],%d,%d", &tscore, &tGA, &FTR, &tHr, &tAr);
		for (int32_t i = 0; i < 20; i++)
		{
			if (!strncmp(tmpHTName, teamList[i].name, 20)) // 重複
			{
				repeat = i;
				break;
			}
		}
		if (repeat == -1) //不重複則新增
		{
			strncpy(teamList[tListIndex].name, tmpHTName, 20);
			teamList[tListIndex].score = tscore;
			teamList[tListIndex].r = tHr;
			teamList[tListIndex].GA = tGA;
			if (FTR == 'H')
			{
				teamList[tListIndex].win = 1;
				teamList[tListIndex].WGH = 1;
				teamList[tListIndex].point = 3;
			}
			else if (FTR == 'D')
			{
				teamList[tListIndex].draw = 1;
				teamList[tListIndex].point = 1;
			}
			else
			{
				teamList[tListIndex].lose = 1;
			}
			tListIndex++;
		}
		else
		{
			teamList[repeat].score += tscore;
			teamList[repeat].r += tHr;
			teamList[repeat].GA += tGA;
			if (FTR == 'H')
			{
				teamList[repeat].win += 1;
				teamList[repeat].WGH += 1;
				teamList[repeat].point += 3;
			}
			else if (FTR == 'D')
			{
				teamList[repeat].draw += 1;
				teamList[repeat].point += 1;
			}
			else
			{
				teamList[repeat].lose += 1;
			}
		}
		// 客場
		// tmp 資料
		repeat = -1;
		for (int32_t i = 0; i < 20; i++)
		{
			if (!strncmp(tmpATName, teamList[i].name, 20)) // 重複
			{
				repeat = i;
				break;
			}
		}
		if (repeat == -1) //不重複則新增
		{
			strncpy(teamList[tListIndex].name, tmpATName, 20);
			teamList[tListIndex].score = tGA;
			teamList[tListIndex].r = tAr;
			teamList[tListIndex].GA = tscore;
			if (FTR == 'A')
			{
				teamList[tListIndex].win = 1;
				teamList[tListIndex].WGA = 1;
				teamList[tListIndex].point = 3;
			}
			else if (FTR == 'D')
			{
				teamList[tListIndex].draw = 1;
				teamList[tListIndex].point = 1;
			}
			else
			{
				teamList[tListIndex].lose = 1;
			}
			tListIndex++;
		}
		else
		{
			teamList[repeat].score += tGA;
			teamList[repeat].r += tAr;
			teamList[repeat].GA += tscore;
			if (FTR == 'A')
			{
				teamList[repeat].win += 1;
				teamList[repeat].WGA += 1;
				teamList[repeat].point += 3;
			}
			else if (FTR == 'D')
			{
				teamList[repeat].draw += 1;
				teamList[repeat].point += 1;
			}
			else
			{
				teamList[repeat].lose += 1;
			}
		}
	}

	printf("1) Who is the winner in this season?\n");
	printf("2) Which team gets the most scores?\n");
	printf("3) Which team gets the most red cards?\n");
	printf("4) Which team wins the most games at home?\n");
	printf("5) Which team wins the most games away from home?\n");
	printf("6) Which game has the most scoring gap?\n");
	printf("7) Team information.\n");
	printf("8) Exit\n");
	while (1) // 功能
	{
		int32_t choice = 0;
		printf("Choice (1-7, 8:exit): ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			winner(teamList);
			break;
		case 2:
			mScore(teamList);
			break;
		case 3:
			mRed(teamList);
			break;
		case 4:
			mWGH(teamList);
			break;
		case 5:
			mWGA(teamList);
			break;
		case 6:
			gameGap(gameList);
			break;
		case 7:
			teamData(teamList);
			break;
		case 8:
			fclose(pFile);
			return 0;
		default:
			break;
		}
	}
	return 0;
}
