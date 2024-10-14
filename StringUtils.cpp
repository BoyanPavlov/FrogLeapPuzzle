#include "StringUtils.hpp"
#include <iostream>
#include <string.h>


int StringUtils::strLen(const char* str)
{
	/* int counter = 0;
	 while (*str)
	 {
		 counter++;
		 str++;
	 }*/
	return strlen(str);

}

int StringUtils::strCmp(const char* text1, const char* text2)
{
	if (text1 == text2)
	{
		return 0;
	}

	if (!text1 || !text2)
	{
		return -1;
	}

	while (*text1 && *text1 == *text2)
	{
		text1++;
		text2++;
	}
	return *text1 - *text2;
}

bool StringUtils::strGreaterThan(const char* text1, const char* text2)
{
	while (*text1 && *text1 == *text2)
	{
		text1++;
		text2++;
	}
	if (*text1 > *text2)
	{
		return true;
	}
	return false;
}
