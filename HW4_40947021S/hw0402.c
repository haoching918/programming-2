#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

struct option long_option[] = {
	{"help", 0, NULL, 'h'},
	{0, 0, 0, 0}};

typedef struct
{
	char origin[32];
	char modified[16];
	int32_t isOccupied;
} variable;

void get_line(char *str, FILE *pFile);
void random_space(FILE *pFile);
void set_name(char *str, variable *var, int32_t type);
int32_t is_Var(char *str, int32_t idx, int32_t type);

void get_line(char *str, FILE *pFile)
{
	char c = 0;
	int32_t idx = 0;

	memset(str, 0, sizeof(str));

	do
	{
		fread(&c, sizeof(char), 1, pFile);
		str[idx++] = c;

	} while (c != ';' && c != '}' && c != '{' && c != '>' && !feof(pFile));

	if (str[0] == '#')
	{
		do
		{
			fread(&c, sizeof(char), 1, pFile);
			if (c == '\n' || c == ' ')
				str[idx++] = c;

		} while (c == '\n' || c == ' ');
		fseek(pFile, -1, SEEK_CUR);
	}
	return;
}

void random_space(FILE *pFile)
{
	char space = ' ';
	char nl = '\n';
	int32_t times = rand() % 5 + 1;

	for (int32_t i = 0; i < times; i++)
	{
		int32_t choice = rand() % 10;

		if (choice < 9)
			fwrite(&space, sizeof(char), 1, pFile);
		else
			fwrite(&nl, sizeof(char), 1, pFile);
	}
	return;
}

void set_name(char *str, variable *var, int32_t type)
{
	int32_t varIdx = 0;
	char tmp[32] = "";

	for (int32_t i = 0; i < 128; i++)
	{
		if (var[i].isOccupied == 0)
		{
			varIdx = i;
			break;
		}
	}
	for (int32_t i = 0; i < strlen(str); i++)
	{
		if (strncmp(&str[i], "int", 3) == 0 || strncmp(&str[i], "char", 4) == 0)
		{
			int32_t continueSearch = 0;
			int32_t strIdx = 0;

			memset(var[varIdx].origin, 0, sizeof(var[varIdx].origin));
			memset(tmp, 0, sizeof(tmp));

			if (type == 0)
			{
				for (int32_t j = i + 4; j < strlen(str); j++)
				{
					if (str[j] == ' ' || str[j] == '\n')
						continue;
					if (str[j] == ';' || str[j] == '=' || str[j] == ',' || str[j] == ')')
						break;
					if (str[j] == '(')
					{
						continueSearch = 1;
						break;
					}

					tmp[strIdx++] = str[j];
				}
			}
			else
			{
				for (int32_t j = i + 4; j < strlen(str); j++)
				{
					if (str[j] == ' ' || str[j] == '\n')
						continue;
					if (str[j] == '(')
						break;
					if (str[j] == ';' || str[j] == '=' || str[j] == ',' || str[j] == ')')
					{
						continueSearch = 1;
						break;
					}
					tmp[strIdx++] = str[j];
				}
			}

			for (int32_t j = 0; j < varIdx; j++)
			{
				if (strncmp(tmp, var[j].origin, strlen(tmp)) == 0)
				{
					continueSearch = 1;
					break;
				}
			}
			if (strncmp(tmp, "main", 4) == 0)
				continueSearch = 1;
			if (continueSearch)
				continue;
			strncpy(var[varIdx].origin, tmp, strlen(tmp));

			var[varIdx].modified[0] = rand() % 26 + 'a';

			for (int32_t j = 1; j < 16; j++)
			{
				int32_t choice = rand() % 62;

				if (choice < 10)
					var[varIdx].modified[j] = choice + '0';
				else if (choice < 36)
					var[varIdx].modified[j] = choice - 10 + 'A';
				else if (choice < 62)
					var[varIdx].modified[j] = choice - 36 + 'a';
			}

			var[varIdx].isOccupied = 1;
			varIdx++;
		}
	}
	return;
}

int32_t is_Var(char *str, int32_t idx, int32_t type)
{
	if (type == 0)
	{
		for (int32_t i = idx; i < strlen(str); i++)
		{
			if (str[i] == ' ' || str[i] == '\n')
				continue;
			if (str[i] == '=' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '<' || str[i] == '>')
				return 1;
			if (str[i] == '&' || str[i] == '^' || str[i] == '|' || str[i] == ')' || str[i] == ',' || str[i] == ';' || str[i] == ':' || str[i] == '!')
				return 1;

			return 0;
		}
	}
	else if (type == 1)
	{
		for (int32_t i = idx; i < strlen(str); i++)
		{
			if (str[i] == ' ' || str[i] == '\n')
				continue;
			if (str[i] == '(')
				return 1;
			return 0;
		}
	}
	else
	{
		for (int32_t i = idx; i >= 0; i--)
		{
			if (str[i] == ' ' || str[i] == '\n')
				continue;
			if (str[i] == '=' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '<' || str[i] == '>')
				return 1;
			if (str[i] == '&' || str[i] == '^' || str[i] == '|' || str[i] == '!' || str[i] == '(' || str[i] == ',')
				return 1;
			if (str[i] == 'e' && i - 3 >= 0)
			{
				if (strncmp(&str[i - 3], "case", 4) == 0)
					return 1;
			}
			if (str[i] == 'n' && i - 5 >= 0)
			{
				if (strncmp(&str[i - 5], "return", 6) == 0)
					return 1;
			}
			return 0;
		}
	}
}

int main(int argc, char *argv[])
{

	int32_t c = 0;
	int32_t level = 0;
	int32_t opt_l = 0;
	int32_t opt_i = 0;
	int32_t opt_o = 0;
	int32_t opt_h = 0;
	char input_filename[32] = "";
	char output_filename[32] = "";

	srand(time(0));

	while ((c = getopt_long(argc, argv, "l:i:o:h", long_option, NULL)) != -1)
	{
		switch (c)
		{
		case 'l':
			opt_l = 1;
			level = (int32_t)strtol(optarg, NULL, 10);
			break;
		case 'i':
			opt_i = 1;
			strncpy(input_filename, optarg, strlen(optarg));
			break;
		case 'o':
			opt_o = 1;
			strncpy(output_filename, optarg, strlen(optarg));
			break;
		case 'h':
			opt_h = 1;
			break;
		}
	}

	if (opt_l && opt_i && opt_o)
	{
		FILE *input_file = NULL;
		FILE *output_file = NULL;
		FILE *tmp_file = NULL;
		int32_t isString = 0;
		char str[1024] = "";
		variable var[128] = {0};

		if ((input_file = fopen(input_filename, "rb")) == NULL)
		{
			perror("Error");
			return 0;
		}
		if ((output_file = fopen(output_filename, "wb+")) == NULL)
		{
			perror("Error");
			return 0;
		}
		if ((tmp_file = fopen("tmp.c", "wb+")) == NULL)
		{
			perror("Error");
			return 0;
		}

		while ((c = fgetc(input_file)) != -1)
			fputc(c, tmp_file);
		for (int32_t i = level; i >= 1; i--)
		{
			rewind(tmp_file);
			rewind(output_file);
			switch (i)
			{
			case 1:
				memset(str, 0, sizeof(str));
				get_line(str, tmp_file);
				while (!feof(tmp_file))
				{
					if (str[0] == '#')
						fwrite(str, strlen(str), 1, output_file);
					else
					{
						isString = 0;
						for (int32_t j = 0; j < strlen(str); j++)
						{

							fwrite(&str[j], sizeof(char), 1, output_file);

							if (str[j] == '\'')
								isString = !isString;
							if (str[j] == '"')
								isString = !isString;
							if (str[j] == ' ' && !isString)
								random_space(output_file);
							if (str[j] == '(' && !isString)
								random_space(output_file);
							if (str[j] == ')' && !isString)
								random_space(output_file);
							if (str[j] == ';' && !isString)
								random_space(output_file);
							if (str[j] == ',' && !isString)
								random_space(output_file);
							if (str[j] == '\n')
								random_space(output_file);
						}
					}

					memset(str, 0, sizeof(str));
					get_line(str, tmp_file);
				}
				break;
			case 2:
				memset(str, 0, sizeof(str));
				get_line(str, tmp_file);
				while (!feof(tmp_file))
				{
					if (str[0] == '#')
						fwrite(str, strlen(str), 1, output_file);
					else
					{
						set_name(str, var, 0);
						isString = 0;
						for (int32_t j = 0; j < strlen(str); j++)
						{

							int32_t varIdx = 0;
							int32_t foundVariable = 0;

							if (str[j] == '\'')
								isString = !isString;
							if (str[j] == '"')
								isString = !isString;

							while (var[varIdx].isOccupied == 1)
							{

								if (strncmp(&str[j], var[varIdx].origin, strlen(var[varIdx].origin)) == 0 && is_Var(str, j + strlen(var[varIdx].origin), 0) && !isString)
								{
									foundVariable = 1;											 
									fwrite(var[varIdx].modified, sizeof(char), 16, output_file);
									j += strlen(var[varIdx].origin) - 1;						
									break;
								}
								varIdx++;
							}
							if (!foundVariable)
								fwrite(&str[j], sizeof(char), 1, output_file);
						}
					}
					memset(str, 0, sizeof(str));
					get_line(str, tmp_file);
				}
				break;
			case 3:
				memset(str, 0, sizeof(str));
				get_line(str, tmp_file);
				while (!feof(tmp_file))
				{
					if (str[0] == '#')
						fwrite(str, strlen(str), 1, output_file);

					else
					{
						set_name(str, var, 1);
						isString = 0;
						for (int32_t j = 0; j < strlen(str); j++)
						{

							int32_t varIdx = 0;
							int32_t foundVariable = 0;

							if (str[j] == '\'')
								isString = !isString;
							if (str[j] == '"')
								isString = !isString;

							while (var[varIdx].isOccupied == 1)
							{

								if (strncmp(&str[j], var[varIdx].origin, strlen(var[varIdx].origin)) == 0 && is_Var(str, j + strlen(var[varIdx].origin), 1) && !isString)
								{
									foundVariable = 1;
									fwrite(var[varIdx].modified, sizeof(char), 16, output_file);
									j += strlen(var[varIdx].origin) - 1;
									break;
								}
								varIdx++;
							}
							if (!foundVariable)
								fwrite(&str[j], sizeof(char), 1, output_file);
						}
					}
					memset(str, 0, sizeof(str));
					get_line(str, tmp_file);
				}
				break;
			case 4:
				memset(str, 0, sizeof(str));
				get_line(str, tmp_file);
				while (!feof(tmp_file))
				{
					if (str[0] == '#')
						fwrite(str, strlen(str), 1, output_file);
					else
					{
						isString = 0;
						for (int32_t j = 0; j < strlen(str); j++)
						{
							if (str[j] == '\'')
								isString = !isString;
							if (str[j] == '"')
								isString = !isString;
							if ((str[j] == '-' && str[j + 1] >= '0' && str[j + 1] <= '9') || (str[j] >= '0' && str[j] <= '9'))
							{
								if (!isString && is_Var(str, j - 1, 2))
								{
									int64_t num = 0;
									char *end = NULL;
									int64_t multiplicand = 0;
									int64_t multiplier = 0;
									int64_t remainder = 0;
									char buf[64] = "";
									num = strtol(&str[j], &end, 10);
									multiplicand = rand() % 50 + 1;
									multiplier = num / multiplicand;
									remainder = num - multiplicand * multiplier;
									if (remainder >= 0)
										snprintf(buf, 64, "( %ld * %ld + %ld )", multiplicand, multiplier, remainder);
									else
										snprintf(buf, 64, "( %ld * %ld - %d )", multiplicand, multiplier, abs(remainder));

									fwrite(buf, sizeof(char), strlen(buf), output_file);
									j += end - &str[j] - 1;
								}
								else
									fwrite(&str[j], sizeof(char), 1, output_file);
							}
							else
								fwrite(&str[j], sizeof(char), 1, output_file);
						}
					}
					memset(str, 0, sizeof(str));
					get_line(str, tmp_file);
				}
				break;
			}
			rewind(output_file);
			tmp_file = freopen(NULL, "wb+", tmp_file);
			while ((c = fgetc(output_file)) != -1)
				fputc(c, tmp_file);
		}
		fclose(input_file);
		fclose(output_file);
		fclose(tmp_file);
		remove("tmp.c");
	}
	if (opt_h)
	{
		printf("./hw0402 -l [options] -i [input file] -o [output file]\n");
		printf("./hw0402 -h\n");
		printf("./hw0402 --help\n");
		printf("    Display this help manual.\n");
	}
	return 0;
}