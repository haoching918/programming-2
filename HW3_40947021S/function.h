#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

// team structure & game structure
typedef struct _steamInfo
{
	char name[20];
	int32_t score;
	int32_t r;	 // red card
	int32_t WGH; // win game home play
	int32_t WGA; // win game away home play
	int32_t win;
	int32_t draw;
	int32_t lose;
	int32_t point;
	int32_t GA; // goal against
} teamInfo;

typedef struct _sgame
{
	char date[11];
	int32_t scoreGap;
	char HT[20];
	char AT[20];
	int32_t HG;
	int32_t AG;
} game;

//function
void gameGap(game *gameList)
{
	int32_t max = 0;
	int32_t maxList[380];
	int32_t count = 0;
	for (int32_t i = 0; i < 380; i++)
	{
		if (gameList[i].scoreGap > max)
		{
			max = gameList[i].scoreGap;
		}
	}
	for (int32_t i = 0; i < 380; i++)
	{
		if (gameList[i].scoreGap == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
		printf("%s,%s(%d) vs %s(%d)\n", gameList[maxList[i]].date, gameList[maxList[i]].HT, gameList[maxList[i]].HG, gameList[maxList[i]].AT, gameList[maxList[i]].AG);
}

void teamData(teamInfo *teamList)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
	char teamName[20] = {0};
	printf("Team: ");
	fgets(teamName, 20, stdin);
	teamName[strlen(teamName) - 1] = '\0';
	for (int32_t i = 0; i < 20; i++)
	{
		if (!strncmp(teamName, teamList[i].name, 20))
		{
			printf("Points: %d\n", teamList[i].point);
			printf("Win/Draw/Lose: %d/%d/%d\n", teamList[i].win, teamList[i].draw, teamList[i].lose);
			printf("Goals Scored/Goals Against: %d/%d\n", teamList[i].score, teamList[i].GA);
			return;
		}
	}
	printf("No data\n");
}

void winner(teamInfo *teamList)
{
	int32_t max = 0;
	int32_t maxList[20];
	int32_t count = 0;
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].point > max)
		{
			max = teamList[i].point;
		}
	}
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].point == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
	{
		printf("The winner is %s\n", teamList[maxList[i]].name);
	}
}

void mScore(teamInfo *teamList)
{
	int32_t max = 0;
	int32_t maxList[20];
	int32_t count = 0;
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].score > max)
			max = teamList[i].score;
	}
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].score == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
		printf("%s, %d\n", teamList[maxList[i]].name, teamList[maxList[i]].score);
}

void mRed(teamInfo *teamList)
{
	int32_t max = 0;
	int32_t maxList[20];
	int32_t count = 0;
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].r > max)
			max = teamList[i].r;
	}
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].r == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
		printf("%s, %d\n", teamList[maxList[i]].name, teamList[maxList[i]].r);
}

void mWGH(teamInfo *teamList)
{
	int32_t max = 0;
	int32_t maxList[20];
	int32_t count = 0;
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].WGH > max)
			max = teamList[i].WGH;
	}
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].WGH == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
		printf("%s, %d\n", teamList[maxList[i]].name, teamList[maxList[i]].WGH);
}

void mWGA(teamInfo *teamList)
{
	int32_t max = 0;
	int32_t maxList[20];
	int32_t count = 0;
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].WGA > max)
			max = teamList[i].WGA;
	}
	for (int32_t i = 0; i < 20; i++)
	{
		if (teamList[i].WGA == max)
		{
			maxList[count] = i;
			count++;
		}
	}
	for (int32_t i = 0; i < count; i++)
		printf("%s, %d\n", teamList[maxList[i]].name, teamList[maxList[i]].WGA);
}