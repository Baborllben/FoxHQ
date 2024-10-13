#pragma once
#define NULL 0
#include <stdio.h>
#include <stdlib.h>

// �ַ���ƴ��
extern "C" char* strspl_tail(
	char* a,			// �ַ���A/
	const char* b		// �ַ���B/
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

// �ַ�����ʽ�������ͷ�
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

// �ַ�����(hang)�ָ���ͷ�
/*
	[pointer]	char str	Ҫ�ָ���ַ���
	[variable]	int	 cursor	���ַ��������￪ʼ
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

// ����ַ�������
extern "C" int checkStrLength(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

// ���ַ������ж�ָ���ַ��Ƿ���ڣ�0 => ���ڣ� 1 => ������
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

// ���ַ�����Ĩ��ĳ�ַ������ͷ�
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