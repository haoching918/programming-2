#include "myprintf.h"

void toInt(int32_t num)
{
	char char_num[10] = {0};
	sprintf(char_num, "%d", num);
	for (int32_t i = 0; i < strlen(char_num); i++)
		fputc(char_num[i], stdout);
}

void toHex(int32_t num)
{
	char char_num[10] = {0};
	sprintf(char_num, "%x", num);
	for (int32_t i = 0; i < strlen(char_num); i++)
		fputc(char_num[i], stdout);
}

void toHeX(int32_t num)
{
	char char_num[10] = {0};
	sprintf(char_num, "%X", num);
	for (int32_t i = 0; i < strlen(char_num); i++)
		fputc(char_num[i], stdout);
}

void toStr(char *str)
{
	for (int32_t i = 0; i < strlen(str); i++)
		fputc(str[i], stdout);
}

int32_t myprintf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t i = 0;
	int32_t formatCount = 0;
	int32_t argCount = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			formatCount++;
			switch (format[i + 1])
			{
			case 'd':
				toInt(va_arg(args, int32_t));
				argCount++;
				break;
			case 'i':
				toInt(va_arg(args, int32_t));
				break;
			case 'x':
				toHex(va_arg(args, int32_t));
				break;
			case 'X':
				toHeX(va_arg(args, int32_t));
				break;
			case 's':
				toStr(va_arg(args, char *));
				break;
			default:
				fputs("error\n", stdout);
				return 1;
				break;
			}
			i += 2;
		}
		else
		{
			fputc(format[i], stdout);
			i++;
		}
	}
	va_end(args);
}
