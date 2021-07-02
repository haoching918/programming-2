#include "stdio.h"
#include "stdint.h"
#include "string.h"
//doraemon.bmp
//doraemonOut.bmp
typedef struct _sBmpHeader
{
	char bm[2];
	uint32_t size; //
	uint32_t reserve;
	uint32_t offset;
	uint32_t header_size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bpp; //4
	uint32_t compression;
	uint32_t bitmap_size; //
	uint32_t hres;
	uint32_t vres;
	uint32_t used;
	uint32_t important;
} __attribute__((__packed__))sBmpHeader;

typedef struct _srgba
{
	uint32_t b : 8;
	uint32_t g : 8;
	uint32_t r : 8;
	uint32_t a : 8;
} __attribute__((__packed__))srgba;

typedef struct _srgb24
{
	uint8_t b, g, r;
} __attribute__((__packed__))rgb24;

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
	int32_t alpha = 0;
	printf("Alpha (0-31): ");
	if (scanf("%d", &alpha) != 1 || alpha < 0 || alpha > 31)
	{
		printf("Invalid input\n");
		return 1;
	}
	if (header.bpp != 24)
	{
		printf("Not 24-bit depth\n");
		return 1;
	}

	header.bpp = 32;
	header.compression = 6;	 
	header.header_size = 56; //
	header.bitmap_size = header.width * header.height * header.bpp / 8;
	header.size = header.bitmap_size + header.header_size;
	header.offset = 70; //
	fwrite(&header, sizeof(header), 1, pWFile);

	rgb24 rgb;
	srgba rgba;
	uint32_t masks[4] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000}; //
	fwrite(masks, sizeof(uint32_t), 4, pWFile);							  //
	while (!feof(pRFile))
	{
		fread(&rgb, 3, 1, pRFile);
		if (alpha == 0)
			rgba.a = 1;
		else
			rgba.a = alpha * 8;
		rgba.r = rgb.r;
		rgba.b = rgb.b;
		rgba.g = rgb.g;
		fwrite(&rgba, 4, 1, pWFile);
	}
	fclose(pRFile);
	fclose(pWFile);

	return 0;
}