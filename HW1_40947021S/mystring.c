#include "mystring.h"

char *mystrchr(const char *s, int c)
{
	char *trav = (char *)s;
	while(*trav != '\0') 
	{
		if(*trav == c) return trav;
		++trav;
	}
	return NULL;
}

char *mystrrchr(const char *s, int c)
{
	int index = strlen(s) - 1;
	while (1)
	{
		if (s[index] == c)
			return (char *)s + index;
		index--;
		if (s[index] == '\0')
			return NULL;
	}
}

size_t mystrspn(const char *s1, const char *s2)
{
	for (int i = 0; i < strlen(s1); i++)
		if(mystrchr(s2, s1[i]) != NULL) return i;
}

size_t mystrcspn(const char *s1, const char *s2)
{
	for (int i = 0; i < strlen(s1); i++)
	{
		for (int j = 0; j < strlen(s2); j++)
		{
			if (s1[i] == s2[j])
				return i;
		}
	}
}

char *mystrpbrk(const char *str1, const char *str2)
{
	for (int i = 0; i < strlen(str1); i++)
	{
		for (int j = 0; j < strlen(str2); j++)
		{
			if (str1[i] == str2[j])
				return (char *)str1 + i;
		}
	}
}

char *mystrstr(const char *haystack, const char *needle)
{
	int found = 0;
	for (int i = 0; i < strlen(haystack); i++)
	{

		for (int j = 0; j < strlen(needle); j++)
		{
			if (haystack[i + j] == needle[j])
			{
				found = 1;
			}
			else
			{
				found = 0;
				break;
			}
		}
		if (found)
		{
			return (char *)haystack + i;
		}
	}
}

char *mystrtok(char *str, const char *delim)
{
	static char *p = 0;
	if (str)
	{
		p = str;
	}
	else if (!p)
	{
		return 0;
	}
	str = p + mystrspn(p, delim);
	p = str + mystrcspn(str, delim);
	if (p == str)
	{
		return p = 0;
	}
	p = *p ? *p = 0, p + 1 : 0;
	return str;
}