#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "string.h"
#include "getopt.h"
#include "math.h"
#include "string.h"

struct option longoptions[] = {
	{"enc", 1, NULL, 'e'},
	{"dec", 1, NULL, 'd'},
	{"output", 1, NULL, 'o'},
	{NULL, 0, NULL, 0}};

void show_help()
{
	printf("\t-e, --enc\t\tEncode a file to a text file.\n");
	printf("\t-d, --dec\t\tDecode a text file to a file.\n");
	printf("\t-o, --output\t\tOutput file name.\n");
}

void ascC_to_b64C(uint8_t *asc_arr, int32_t len) // 使之正確顯示b64字元
{
	for (int32_t i = 0; i < len; i++)
	{
		uint8_t c = asc_arr[i]; 
		if (c <= 61 && c >= 52) // ASCII 0 為 48 base64 0 為 52
			asc_arr[i] -= 4;
		else if (c >= 0 && c <= 25)
			asc_arr[i] += 65;
		else if (c >= 26 && c <= 51)
			asc_arr[i] += 71;
		else if (asc_arr[i] == 62)
			asc_arr[i] = '+';
		else if (asc_arr[i] == 63)
			asc_arr[i] = '/';
	}
}
  
void b64_to_idx(uint8_t *b64_arr, int32_t len) // 轉換b64字元到對應binary
{
	for (size_t i = 0; i < len; i++)
	{
		uint8_t c = b64_arr[i];
		if (c == '=')
			return;
		else if (c >= 65 && c <= 90)
			b64_arr[i] -= 65;
		else if (c >= 97 && c <= 122)
			b64_arr[i] -= 71;
		else if (c <= 57 && c >= 48)
			b64_arr[i] += 4;
		else if (c == '+')
			b64_arr[i] = 62;
		else if (c == '/')
			b64_arr[i] = 63;
	}
}

void encode(char *iFileName, char *oFileName)
{
	FILE *iFile = NULL;
	FILE *oFile = NULL;
	int32_t count = 0;	   // 決定是否需要 padding
	uint8_t octets[3] = {0};  // 8 個為一組有3組
	uint8_t sextets[4] = {0}; // 6 個為一組有4組

	if ((iFile = fopen(iFileName, "r")) == NULL)
	{
		perror("Error");
		return;
	}
	if ((oFile = fopen(oFileName, "w")) == NULL)
	{
		perror("Error");
		return;
	}

	while ((count = fread(octets, 1, 3, iFile)) == 3) // 整除 3
	{
		int8_t bin_arr[24] = {0};		// 二進位陣列
		for (int32_t i = 0; i < 3; i++) // 取得二進位資料
		{
			uint8_t tmp = octets[i];
			for (int32_t j = i * 8 + 8 - 1; j >= i * 8; j--)
			{
				bin_arr[j] = tmp % 2;
				tmp /= 2;
			}
		}
	
		for (int32_t i = 0; i < 4; i++) // 6bit一組
		{
			int32_t exponent = 0;
			sextets[i] = 0;
			for (int32_t j = i * 6 + 6 - 1; j >= i * 6; j--)
			{
				sextets[i] += pow(2, exponent) * bin_arr[j];
				exponent++;
			}
		}
	
		ascC_to_b64C(sextets, 4);
		
		fwrite(sextets, 1, 4, oFile);
		
	}
	if (count == 2) // 餘 2
	{
		int8_t bin_arr[24] = {0};
		for (int32_t i = 0; i < 2; i++) 
		{
			int8_t tmp = octets[i];
			for (int32_t j = i * 8 + 8 - 1; j >= i * 8; j--)
			{
				bin_arr[j] = tmp % 2;
				tmp /= 2;
			}
		}

		for (int32_t i = 0; i < 3; i++)
		{
			int32_t exponent = 0; // 指數
			sextets[i] = 0;
			for (int32_t j = i * 6 + 6 - 1; j >= i * 6; j--)
			{
				sextets[i] += pow(2, exponent) * bin_arr[j];
				exponent++;
			}
		}

		ascC_to_b64C(sextets, 3);
		sextets[3] = '='; // padding

		fwrite(sextets, 1, 4, oFile);
	}
	else if (count == 1) // 餘 1
	{
		int8_t bin_arr[24] = {0};
		for (int32_t i = 0; i < 1; i++)
		{
			int8_t tmp = octets[i];
			for (int32_t j = i * 8 + 8 - 1; j >= i * 8; j--)
			{
				bin_arr[j] = tmp % 2;
				tmp /= 2;
			}
		}

		for (int32_t i = 0; i < 2; i++)
		{
			int32_t exponent = 0;
			sextets[i] = 0;
			for (int32_t j = i * 6 + 6 - 1; j >= i * 6; j--)
			{
				sextets[i] += pow(2, exponent) * bin_arr[j];
				exponent++;
			}
		}

		ascC_to_b64C(sextets, 2);
		sextets[2] = '=';
		sextets[3] = '=';

		fwrite(sextets, 1, 4, oFile);
	}

	fclose(iFile);
	fclose(oFile);
}

void decode(char *iFileName, char *oFileName)
{
	FILE *iFile = NULL;
	FILE *oFile = NULL;
	int8_t octets[3] = {0};
	uint8_t sextets[4] = {0};

	if ((iFile = fopen(iFileName, "r")) == NULL)
	{
		perror("Error");
		return;
	}
	if ((oFile = fopen(oFileName, "w")) == NULL)
	{
		perror("Error");
		return;
	}

	while (1)
	{
		int8_t bin_arr[24] = {0};
		int32_t padding = 0; 

		fread(sextets, 1, 4, iFile);
		if (feof(iFile)) break;
		
		for (int32_t i = 0; i < 4; i++) // 計算 padding 數量
		{
			if (sextets[i] == '=')
			{
				padding = 4 - i;
				break;
			}
		}
		
		b64_to_idx(sextets, 4); 
		for (int32_t i = 0; i < 4 - padding; i++)
		{
			uint8_t tmp = sextets[i];
			for (int32_t j = i * 6 + 6 - 1; j >= i * 6; j--)
			{
				bin_arr[j] = tmp % 2;
				tmp /= 2;
			}
		}
	
		for (int32_t i = 0; i < 3 - padding; i++)
		{
			octets[i] = 0;
			int32_t exponent = 0;
			for (int32_t j = i * 8 + 8 - 1; j >= i * 8; j--)
			{
				octets[i] += (pow(2, exponent) * bin_arr[j]);
				exponent++;
			}
		}
		fwrite(octets, 1, 3 - padding, oFile);
	}

	fclose(iFile);
	fclose(oFile);
}

int32_t main(int argc, char *argv[])
{
	char opt;
	char iFileName[32] = {0};
	char oFileName[32] = {0};
	int32_t is_help = 0;
	int32_t is_enc = 0;
	int32_t is_dec = 0;
	while ((opt = getopt_long(argc, argv, "e:d:o:h", longoptions, NULL)) != -1)
	{
		switch (opt)
		{
		case 'h':
			is_help = 1;
			break;
		case 'o':
			strncpy(oFileName, optarg, 32);
			break;
		case 'e':
			is_enc = 1;
			strncpy(iFileName, optarg, 32);
			break;
		case 'd':
			is_dec = 1;
			strncpy(iFileName, optarg, 32);
			if (strncmp(".txt", iFileName + strlen(iFileName) - 4, 4) != 0) // 判斷為 txt 檔
			{
				printf("Not txt file\n");
				return 1;
			}
			break;
		case '?':
			printf("Option doesn't exist or too many argument\n");
			return 1;
			break;
		default:
			break;
		}
	}

	if (is_help)
		show_help();
	if (is_dec && is_enc)
	{
		printf("One mode at a time\n");
		return 1;
	}
	if (is_dec)
		decode(iFileName, oFileName);
	if (is_enc)
		encode(iFileName, oFileName);

	return 0;
}
