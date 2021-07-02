#include "curl/curl.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "unistd.h"
#include "getopt.h"
#include "string.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "sys/mman.h"

typedef char string[300];
void query();
uint64_t getFDSize(int32_t fd);
const char *bufferFile = "websiteData.buf";
int main(int32_t argc, char *argv[])
{
    int32_t c = -1, help = 0;
    char *keywordURL = NULL;
    const char *URL = "https://dblp.org/search?q=";
    uint32_t size = 0;
    while ((c = getopt(argc, argv, "q:h")) != -1)
    {
        switch (c)
        {
        case 'h':
            help = 1;
            break;
        case 'q':
            if (optarg)
            {
                size = strlen(optarg) + strlen("https://dblp.org/search?q=") + 3;
                keywordURL = (char *)calloc(size, sizeof(char));
                strncpy(keywordURL, "https://dblp.org/search?q=", strlen(URL));
                strncat(keywordURL, optarg, strlen(optarg));
            }
            break;
        default:
            break;
        }
    }
    if (help)
    {
        printf("\t./hw0503 -q keyword\n");
    }
    else
    {
        CURL *curl = curl_easy_init();
        CURLcode res;
        if (curl)
        {
            FILE *buf = fopen(bufferFile, "w");

            curl_easy_setopt(curl, CURLOPT_URL, keywordURL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                printf("curL_easy_perform() failed.\n");

            fclose(buf);

            query();
        }
        curl_easy_cleanup(curl);

        remove(bufferFile);
    }
    free(keywordURL);
    return 0;
}

void query()
{
    const char *par = "<cite class=\"data\" itemprop=\"headline\">";
    const char *authorPar = "<span itemprop=\"name\" title=\"";
    const char *titlePar = "<span class=\"title\" itemprop=\"name\">";
    const char *datePar = "<span itemprop=\"datePublished\">";
    const char *sourcePar = "<span itemprop=\"name\">";
    int32_t fd = 0;
    fd = open(bufferFile, O_RDWR);

    uint64_t fSize = getFDSize(fd);
    char *pointer = NULL;
    pointer = mmap(0, fSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    char *str = NULL;

    str = strstr(pointer, par);
    int32_t counter = 0; 

    while (str != NULL)
    {
        if (counter >= 10) break;
        str = str + strlen(par);
        char *endOfStr = strstr(str, par);

        if (endOfStr != NULL) *(endOfStr - 1) = 0;
        
        string author[100] = {0};
        char *pointer = strstr(str, authorPar);
        char *token = NULL;
        int32_t authorcounter = 0;
        if (pointer == NULL)
        {
            strncpy(author[0], "No author", sizeof(string) - 5);
            authorcounter = 1;
        }
        {
            while (pointer != NULL)
            {
                pointer += strlen(authorPar);
                token = strtok(pointer, "\"");
                strncpy(author[authorcounter], token, sizeof(string) - 5);
                pointer = token + 1 + strlen(token);
                *(pointer - 1) = '\"';
                pointer = strstr(pointer, authorPar);
                authorcounter++;
            }
        }
        pointer = NULL;
        token = NULL;
        
        string title = {0};
        pointer = strstr(str, titlePar);
        if (pointer == NULL)
        {
            strncpy(title, "No title", sizeof(string) - 5);
        }
        {
            pointer += strlen(titlePar);
            token = strtok(pointer, "<");
            strncpy(title, token, sizeof(string) - 5);
            *(token + strlen(token)) = '<';
            pointer = NULL;
            token = NULL;
        }
        
        string date = {0};
        pointer = strstr(str, datePar);
        if (pointer == NULL)
        {
            strncpy(date, "No date", sizeof(string) - 5);
        }
        else
        {
            *(pointer - 1) = 0;
            pointer += strlen(datePar);
            token = strtok(pointer, "<");
            strncpy(date, token, sizeof(string) - 5);
        }
        
        string source = {0};
        pointer = strstr(str, sourcePar);
        if (pointer == NULL)
        {
            strncpy(source, "No source", sizeof(string) - 5);
        }
        else
        {
            pointer += strlen(sourcePar);
            token = strtok(pointer, "<");
            while (token != NULL)
            {
                strncat(source, token, sizeof(string) - 5);
                token = strtok(NULL, "<");
                if (token == NULL)
                    break;
                token = strchr(token, '>');
                if (token != NULL)
                    token++;
            }
        }
        
        printf("Paper %2d\n", counter + 1);
        printf("\tTitle : %s\n", title);
        printf("\tAuthor : ");
        for (int32_t i = 0; i < authorcounter; i++)
        {
            printf("%s", author[i]);
            if (i != authorcounter - 1)
                printf(", ");
        }
        printf("\n\tSource : %s\n", source);
        printf("\tDate : %s\n", date);
        
        counter++;
        if (endOfStr == NULL) break;
        else str = strstr(endOfStr, par);
    }

    munmap(pointer, fSize);
    close(fd);
    return;
}

uint64_t getFDSize(int32_t fd)
{
    struct stat statBuf;
    if (fstat(fd, &statBuf) < 0)
    {
        return -1;
    }
    return statBuf.st_size;
}