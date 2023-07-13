#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
char str[100];
int flag[100];//记录字母出现的次数
char mima[26];//生成的密码
char yuanma[50];//输入的单词
int main()
{
	int i = 0, j = 0;;
	gets(yuanma);
	while (yuanma[i] != '\0')
	{
		if (flag[yuanma[i] - 'a'] == 0)
		{
			flag[yuanma[i] - 'a']++;
			mima[j++] = yuanma[i++];
		}
		else
		{
			i++;
		}
	}
	int len = strlen(mima),cnt=25;
	for (i = len; i <= 25; cnt--)
	{
		if (flag[cnt] == 0)
		{
			mima[i] = 'a' + cnt;
			i++;
		}
		else
		{
			continue;
		}
	}
	//printf("%s", mima);
	FILE* Rstream = fopen("encrypt.txt", "r");
	FILE* Wstream = fopen("output.txt", "w");
	if (fgets(str, 100, Rstream) != NULL)
	{
		for (i = 0; i < strlen(str); i++)
		{
			if (!isalpha(str[i]))
			{
				fputc(str[i], Wstream);
			}
			else
			{
				fputc( mima[str[i] - 'a'],Wstream);
			}
		}
	}
	fclose(Rstream);
	fclose(Wstream);
	return 0;
}
