#pragma once
#define NULL 0
#include <stdio.h>
#include <stdlib.h>

// 字符串拼接
extern "C" char* strspl_tail(
	char* a,			// 字符串A/
	const char* b		// 字符串B/
)
{
	int a_len = 0;
	while (a[a_len] != '\0') a_len++;
	int b_len = 0;
	while (b[b_len] != '\0') b_len++;
	if (a_len > a_len + b_len)
	{
		return NULL;
	}

	static char* c = a;
	for (int i = 0; i < b_len; i++)
	{
		c[a_len] = b[i];
		a_len++;
	}
	return c;
}

// 字符串格式化（需释放
extern "C" char* formatStr(char* str)
{
	static char* result = (char*)calloc(12800, sizeof(char));;
	int i = 0;
	int a = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\r' || str[i] == '\b' || str[i] == '\t')
		{
			i++;
			continue;
		}
		result[a] = str[i];
		i++;
		a++;
	}
	return result;
}

// 字符串行(hang)分割（需释放
/*
	[pointer]	char str	要分割的字符串
	[variable]	int	 cursor	从字符串的哪里开始
*/
extern "C" char* lineSplitStr(char* str, int cursor)
{
	static char* result = (char*)calloc(1024, sizeof(char));
	int a = 0;
	while (str[cursor] != '\0')
	{
		if (str[cursor] == '\n')
		{
			return result;
		}
		result[a] = str[cursor];
		cursor++;
		a++;
		//printf("%d | ", a);
	}
	return result;
}

// 检测字符串长度
extern "C" int checkStrLength(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

// 在字符串中判断指定字符是否存在（0 => 存在； 1 => 不存在
extern "C" int checkCharExistInStr(char* str, const char charactor)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == charactor) return 0;
		i++;
	}
	return 1;
}

// 在字符串内抹除某字符（需释放
extern "C" char* deleteCharInStr(char* str, const char charactor)
{
	int i = 0;
	static char* result = (char*)calloc(1024, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == charactor) continue;
		result[i] = str[i];
		i++;
	}
	return result;
}