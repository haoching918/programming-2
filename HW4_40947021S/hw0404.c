#include "stdio.h"
#include "stdint.h"
#include "string.h"

typedef struct _slocal_header
{
    uint32_t PK;
    char buf[22];
    uint16_t file_name_lenth;
    uint16_t extra_field_lenth;
} __attribute__((__packed__)) slocal_header;

int32_t slash_Count(char *pathname)
{
    int32_t len = strlen(pathname);
    int32_t count = 0;
    for (int32_t i = 0; i < len; i++)
    {
        if (pathname[i] == '/')
            count++;
    }
    return count;
}

int32_t main(int argc, char const *argv[])
{
    if (argc > 2)
    {
        printf("too many argument\n");
        return 1;
    }

    printf(".\n");
    char input_filename[32] = {0};
    strncpy(input_filename, argv[1], 32);
    FILE *pfile = NULL;
    if ((pfile = fopen(input_filename, "r")) == NULL)
    {
        printf("error\n");
        return 0;
    }
    char root_name[32] = {0};
    slocal_header root_header;
    fseek(pfile, 30 + strlen(input_filename) - 4 + 1, SEEK_SET); // 扣除".zip"加上"/"
    
    while (!feof(pfile))
    {
        uint32_t testPK;
        fread(&testPK, 4, 1, pfile); // 確保為 local header file
        if (testPK == 0x06054b50)
            break;
        else if (testPK != 0x04034b50)
        {
            fseek(pfile, -3, SEEK_CUR);
            continue;
        }
        else
            fseek(pfile, -4, SEEK_CUR);
        slocal_header header;
        fread(&header, sizeof(slocal_header), 1, pfile);
        char pathname[32] = {0};
        fread(pathname, header.file_name_lenth, 1, pfile);
        
        int32_t slashCount = slash_Count(pathname);
        int32_t tabCount = slash_Count(pathname) - 1 - 1; // 扣除根目錄、第一個目錄
        if (pathname[strlen(pathname) - 1] == '/') // 目錄
        {
            char *filename;
            filename = strtok(pathname, "/");          // 取得根目錄
            for (int32_t i = 0; i < slashCount - 1; i++) // 扣掉上一次
                filename = strtok(NULL, "/");
            for (int32_t i = 0; i < tabCount; i++) // 扣除根目錄、第一個目錄
                printf("    ");
            printf("+-- %s/", filename);
        }
        else // 檔案
        {
            char *filename;
            filename = strtok(pathname, "/");              // 取得根目錄
            for (int32_t i = 0; i < slashCount - 1 + 1; i++) // 扣除根目錄
                filename = strtok(NULL, "/");
            for (int32_t i = 0; i < tabCount + 1; i++) // 本身為檔案
                printf("    ");
            printf("+-- %s", filename);
        }
        printf("\n");
    }
    return 0;
}
