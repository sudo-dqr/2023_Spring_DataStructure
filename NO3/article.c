#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
//用数组实现 用字符型二维数组的不同行存储单词
char wordlist[1000][500];
int cmp(const void* a, const void* b)
{
	return (strcmp((char*)a, (char*)b));
}
int main()
{
	int flag = 1;//标记是否开始读入单词
	int cnt = 0;
	int place = 0;
	FILE* RSTREAM = fopen("article.txt", "r");

	char ch = fgetc(RSTREAM);
	while (ch != EOF)
	{
		if (isalpha(ch))
		{
			flag = 0;
			wordlist[cnt][place] = tolower(ch);
			place++;
		}
		else
		{
			if (flag != 1)
			{
				cnt++;
				wordlist[cnt][place] = '\0';
                        flag = 1;
			      place = 0;
			}
		}
		ch = fgetc(RSTREAM);
	}

	fclose(RSTREAM);
	qsort(wordlist, cnt, sizeof(wordlist[0]), cmp);
	int i;
	for (i = 0; i < cnt; i++)
	{
		int count = 1;
		int now = i+1;
		while (strcmp(wordlist[i], wordlist[now]) == 0)
		{
			now++;
			count++;
		}
		printf("%s %d\n", wordlist[i], count);
		i = now - 1;
	}
	return 0;
}

