#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
//指定文件中某一字符串替换为另一个字符串
//指定的被替换字符串大小写无关
char src[100] = "";
char sub[100] = "";
char str[100] = "";
int my_strstr(char[], char[]);
int main()
{
	gets(src);
	gets(sub);
	FILE* Rstream = fopen("filein.txt", "r");
	FILE* Wstream = fopen("fileout.txt", "w");
	while (fgets(str, 100, Rstream) != NULL)//按照行形式读入文件
	{
		int i = 0, j = 0;
		for (i = 0; i < strlen(str); i++)
		{
			if (my_strstr(str + i, src) == 0)//逐位进行比对返回值为0时说明刚好在头部对齐
			{
				fputs(sub, Wstream);
				i = i + strlen(src) - 1;
			}
			else//不在头部对齐就先输出前面的字符
			{
				fputc(str[i], Wstream);
			}
		}
	}

	fclose(Rstream);
	fclose(Wstream);
	return 0;
}
int my_strstr(char str[], char src[])//在读入文件的每一行中查找是否含有需要替换的字符串，返回出现的位置
{
	//先将字符串转换为大写
	int i = 0,j=0;
	char temp1[100] = "";
	char temp2[100] = "";
	strcpy(temp1, str);
	strcpy(temp2, src);
	for (i = 0; i < strlen(temp1); i++)
	{
		temp1[i] = toupper(temp1[i]);
	}
	for (i = 0; i < strlen(temp2); i++)
	{
		temp2[i] = toupper(temp2[i]);
	}
	i = 0, j = 0;
	while (temp1[i] != '\0' && temp2[i] != '\0')
	{
		if (temp1[i] == temp2[j])
		{
			i++;
			j++;
		}
		else//字符不等则s中退回到上次查找的下一个位置
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (temp2[j] == '\0')
		return i - j;
	else
		return -1;
}

