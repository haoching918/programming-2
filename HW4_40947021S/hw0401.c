#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

struct option long_options[] = {
	{"size", 1, NULL, 'z'},
	{"help", 0, NULL, 'h'},
	{0, 0, 0, 0}};

void show_help()
{
	printf("Split:\n");
	printf("./hw0401 -s [file] --size [Small File Size]\n");
	printf("The default small file size is 1000 bytes.\n");
	printf("Recover:\n");
	printf("./hw0401 -r [output file] [small files]\n");
	printf("The input small files may not be in order.\n");
}

void seperate(char *filename, int32_t size)
{
	FILE *iFile = NULL;
	int32_t count = 0;
	uint8_t order = '1';

	if ((iFile = fopen(filename, "r")) == NULL)
	{
		printf("Can`t open\n");
		return;
	}

	while (!feof(iFile))
	{
		char OutputFileName[32] = {0};
		char buf[1000000] = {0};
		FILE *ofile = NULL;

		strncpy(OutputFileName, filename, 32);
		strncat(OutputFileName, ".", 1);
		strncat(OutputFileName, &order, 1);
		printf("%s ", OutputFileName);

		if ((ofile = fopen(OutputFileName, "w")) == NULL)
		{
			perror("Error");
			exit(1);
		}
		count = fread(buf, 1, size, iFile);
		fwrite(buf, 1, count, ofile);
		fclose(ofile);

		order++;
	}

	printf("\n");
	fclose(iFile);
}

int32_t get_fileSize(FILE *file)
{
	int32_t size = 0;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	return size;
}

void recover(char *outputFileName, char *inputFileName[], int32_t inputFileCnt)
{
	for (int32_t i = 0; i < inputFileCnt; i++) // 排序
	{
		for (int32_t j = i; j < inputFileCnt; j++)
		{
			if (inputFileName[i][strlen(inputFileName[i]) - 1] > inputFileName[j][strlen(inputFileName[j]) - 1])
			{
				char *tmp = inputFileName[i];
				inputFileName[i] = inputFileName[j];
				inputFileName[j] = tmp;
			}
		}
	}

	FILE *oFile = NULL;
	oFile = fopen(outputFileName, "w");

	for (int32_t i = 0; i < inputFileCnt; i++)
	{
		char buf[1000000] = {0};
		FILE *iFile = NULL;
		if ((iFile = fopen(inputFileName[i], "r")) == NULL)
		{
			perror("Error");
			exit(1);
		}
		fread(buf, 1, get_fileSize(iFile), iFile);
		fwrite(buf, 1, get_fileSize(iFile), oFile);
		fclose(iFile);
	}
	fclose(oFile);
}

int32_t main(int32_t argc, char *argv[])
{
	char opt;
	char filename[32] = {0};
	char *inputFileName[] = {NULL};
	char newFileName[32] = {0};
	int32_t mode = 0;
	int32_t inputFileCnt = 0;
	int32_t size = 1000;
	int32_t is_help = 0;
	int32_t ind = 0;

	while ((opt = getopt_long(argc, argv, "s:r:", long_options, NULL)) != -1)
	{
		switch (opt)
		{
		case 'h':
			is_help = 1;
			break;
		case 'z':
			size = strtol(optarg, NULL, 10);
			break;
		case 's':
			mode = 1;
			strncpy(filename, optarg, 32);
			break;
		case 'r':
			ind = optind;
			strncpy(newFileName, argv[optind - 1], 32);
			mode = 2;
			while (ind != argc)
			{
				if (argv[ind][0] == '-')
					break;
				inputFileName[inputFileCnt] = argv[ind];
				inputFileCnt++;
				ind++;
			}
		default:
			break;
		}
	}
	if (is_help)
		show_help();
	if (mode == 1)
		seperate(filename, size);
	else if (mode == 2)
		recover(newFileName, inputFileName, inputFileCnt);
	return 0;
}
