#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
char src[200];
char sub[200];
int flag = 0;//标记读取源字符串到达的的位置
int cmp(const void* a, const void* b)
{
	return(strcmp((char*)a, (char*)b));
}
char* getsign(char src[],char s[])
{
	int i = flag, j = 0;
	while (!ok(src[i])&&(flag<strlen(src)))
	{
		i++;
		flag++;
	}
	while (ok(src[i])&&(flag<strlen(src)))
	{
		s[j] = src[i];
		i++, j++,flag++;
	}
	s[j] = '\0';
	return s;
}
int ok(char ch)
{
	if (ch == '_' || isalpha(ch) || isdigit(ch))
		return 1;
}
int allnum(char s[])
{
	int i=0;
	int cnt = 0;
	while (s[i] != '\0')
	{
		if (isdigit(s[i]))
		{
			cnt++;
		}
		i++;
	}
	return (cnt == strlen(s));
}
char a[500][50];
int row = 0;
int find(char* p)//查重
{
	int i;
	for (i = 0; i <= row; i++)
	{
		if (strcmp(p, a[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	gets(src);
	while (flag < strlen(src))
	{
		char s[50];
		char* p = getsign(src,s);
		if (!allnum(p)&&(!find(p)))
		{
			strcpy(a[row], p);
			row++;
		}
	}
	qsort(a, row, sizeof(a[0]), cmp);
	int i;
	for (i = 0; i <= row; i++)
	{
		printf("%s ", a[i]);
	}
	return 0;
}

