#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
int chess[20][20];//初始状态下置为0
int autofindfour(int, int);
int hangfind(int, int, int);
int liefind(int, int, int);
int xiezuofind(int, int, int);
int xieyoufind(int, int, int);
int main()
{
	int i, j;
	for (i = 1; i <= 19; i++)
	{
		for (j = 1; j <= 19; j++)
		{
			scanf("%d", &chess[i][j]);
		}
	}//存入棋盘

	for (i = 1; i <= 19; i++)
	{
		for (j = 1; j <= 19; j++)
		{
			int a = autofindfour(i, j);
			if (a == -1)
				continue;
			else if (a == 1)
			{
				printf("1:%d,%d\n", i, j);
				return 0;
			}
			else if (a == 2)
			{
				printf("2:%d,%d\n", i, j);
				return 0;
			}
		}
	}
	printf("No\n");
	return 0;
}
int autofindfour(int i, int j)
{
	if (chess[i][j] == 0)
		return -1;
	else {
		int color = chess[i][j];
		if (hangfind(i, j, color) > 0 || liefind(i, j, color) > 0 || xiezuofind(i, j, color) > 0 || xieyoufind(i, j, color) > 0)
			return color;//四个方向有一个方向找到就满足条件
		else
			return -1;//都没找到
	}
}
int hangfind(int i, int j, int color)
{
	int k = 0, cnt = 0;
	for (k = 0; (k <= 3)&&(i+k<=19); k++)
	{
		if (chess[i + k][j] == color)
			cnt++;
	}
	if ((cnt == 4 )&& (i + 4 <= 19) &&( chess[i + 4][j] == 0))
		return 1;
	else if ((cnt == 4) && (i - 1 >= 1) && (chess[i - 1][j] == 0))
		return 1;
	else
		return -1;
}
int liefind(int i, int j, int color)
{
	int k = 0, cnt = 0;
	for (k = 0; (k <= 3)&&(j+k<=19); k++)
	{
		if (chess[i][j + k] == color)
		{
			cnt++;
		}
		if ((cnt == 4) && (j + 4 <= 19) &&( chess[i][j + 4] == 0))
			return 1;
		if ((cnt == 4) && (j - 1 >= 1) &&( chess[i][j - 1] == 0))
			return 1;
		else
			return -1;
	}
}
int xiezuofind(int i, int j, int color)
{
	int k = 0, cnt = 0;
	for (k = 0; (k <= 3)&&(i + 3 <= 19)&&(j - 3 >= 1); k++)
	{
		if (chess[i + k][j - k] == color)
			cnt++;
	}
	if ((cnt == 4) && (i + 4 <= 19) && (j - 4 >= 1) && (chess[i + 4][j - 4] == 0))
		return 1;
	else if ((cnt == 4 )&& (i - 1 >= 1) && (j + 1 <= 19) &&( chess[i - 1][j + 1] == 0))
		return 1;
	else
		return -1;
}
int xieyoufind(int i, int j, int color)
{
	int k = 0, cnt = 0;
	for (k = 0; (k <= 3)&&(i + 3 <= 19)&&( j + 3 <= 19); k++)
	{
		if (chess[i + k][j + k] == color)
		{
			cnt++;
		}
	}
	if ((cnt == 4) && (i + 4 <= 19) && (j + 4 <= 19) &&( chess[i + 4][j + 4] == 0))
		return 1;
	else if ((cnt == 4 )&& (i - 1 >= 1) && (j - 1 >= 1) &&( chess[i - 1][j - 1] == 0))
		return 1;
	else
		return -1;
}

