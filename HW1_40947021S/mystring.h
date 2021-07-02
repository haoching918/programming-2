#include<stdio.h>
#include<stdint.h>
#include<string.h>


char *mystrchr(const char *s, int c);
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s1, const char *s2);
size_t mystrcspn(const char *s1, const char *s2);
char *mystrpbrk(const char *str1, const char *str2);
char *mystrstr(const char *haystack, const char *needle);
char *mystrtok(char *str, const char *delim);