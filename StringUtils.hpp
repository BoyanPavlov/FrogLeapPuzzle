#pragma once

#ifndef _UTILITIES_
#define _UTILITIES_

class StringUtils
{
public:
	//static void strCpy(char* dest, const char* src);

	static int strLen(const char* str);

	static int strCmp(const char* text1, const char* text2);

	static bool strGreaterThan(const char* text1, const char* text2);
};

#endif // _UTILITIES_