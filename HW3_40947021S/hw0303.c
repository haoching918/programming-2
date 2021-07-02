#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "math.h"
//doraemon.bmp
//doraemonOut.bmp
struct _sBmpHeader
{
	char bm[2];
	uint32_t size; //
	uint32_t reserve;
	uint32_t offset;
	uint32_t header_size;
	uint32_t width; //
	uint32_t height;
	uint16_t planes;
	uint16_t bpp;
	uint32_t compression;
	uint32_t bitmap_size; //
	uint32_t hres;
	uint32_t vres;
	uint32_t used;
	uint32_t important;
} __attribute__((__packed__));

typedef struct _sBmpHeader sBmpHeader;

int32_t main()
{
	FILE *pRFile = NULL;
	FILE *pWFile = NULL;
	char Inputfilename[32] = {0};
	char outputfilename[32] = {0};

	printf("Please input a BMP file: ");
	fgets(Inputfilename, 32, stdin);
	printf("Please input the output BMP file name: ");
	fgets(outputfilename, 32, stdin);
	Inputfilename[strlen(Inputfilename) - 1] = '\0';
	outputfilename[strlen(outputfilename) - 1] = '\0';

	if ((pRFile = fopen(Inputfilename, "rb")) == NULL)
	{
		printf("Can't open \n");
		return 1;
	}
	if ((pWFile = fopen(outputfilename, "wb")) == NULL)
	{
		printf("Can't open \n");
		return 1;
	}

	sBmpHeader header;
	fread(&header, sizeof(header), 1, pRFile);
	
	double angle = 0;
	printf("Angle (0-90): ");
	if (scanf("%lf", &angle) != 1 || angle <= 0 || angle > 90)
	{
		printf("Invalid input\n");
		return 1;
	}

	int32_t preWidth = header.width;
	// 調整 header
	header.width = header.height * tan(((90 - angle) / 180) * M_PI) + preWidth;
	if (header.width % 4 != 0) // width 須為 4 的倍數
		header.width += (4 - header.width % 4);
	header.bitmap_size = header.width * header.height * header.bpp / 8;
	header.size = header.bitmap_size + header.header_size;
	fwrite(&header, sizeof(header), 1, pWFile);

	int32_t cur_height = header.height;

	while (!feof(pRFile))
	{
		uint8_t original[100000] = {0};
		uint8_t white_pix[100000];
		for (size_t i = 0; i < 100000; i++)
			white_pix[i] = 255;
		// 計算左右空白像素數
		int32_t right_white_pix = cur_height * tan(((90 - angle) / 180) * M_PI);
		int32_t left_white_pix = header.width - right_white_pix - preWidth;

		fread(original, 1, preWidth * header.bpp / 8, pRFile);

		fwrite(white_pix, 1, left_white_pix * header.bpp / 8, pWFile);
		fwrite(original, 1, preWidth * header.bpp / 8, pWFile);
		fwrite(white_pix, 1, right_white_pix * header.bpp / 8, pWFile);
		cur_height--;
	}
	fclose(pRFile);
	fclose(pWFile);

	return 0;
}
