#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
姓名和号码都相同——重复项，只保留第一项
姓名相同电话号码不同——首次出现不做处理，第n次重复 名字_n;
*/
struct lianxiren
{
	int flag;//记录序号
	char name[100];
	char num[100];
};
void optiBubbleSort(struct lianxiren[], int n);
char NAME[100], NUM[100];//临时存放输入的字符串
struct lianxiren tongxunlu[200] ;
int main()
{ 
	int n ,i ,j , cnt=1,x=1;
	scanf("%d", &n);
	scanf("%s", tongxunlu[0].name);
	scanf("%s", tongxunlu[0].num);
	for (i = 1; i < n; i++)
	{
		scanf("%s", NAME);
		scanf("%s", NUM);
		int sum = 0;
		for (j = 0; j <= i - 1; j++)
		{
			if ((strcmp(NAME, tongxunlu[j].name) == 0) && (strcmp(NUM, tongxunlu[j].num) == 0))
			{
				sum++;
			}
		}
		if (sum == 0)
		{
			strcpy(tongxunlu[x].name, NAME);
			strcpy(tongxunlu[x].num, NUM);
			cnt++;
			x++;
		}
	}
	/*printf("\n");
	for (i = 0; i < cnt; i++)
	{
		printf("%s %s\n", tongxunlu[i].name, tongxunlu[i].num);
	}
	printf("\n");
	*/
	for (i = 0; i < cnt; i++)//对名字相同的进行标号
	{
		int a = 0;
		for (j = i + 1; j < cnt; j++)//往后寻找
		{
			if ((strcmp(tongxunlu[i].name, tongxunlu[j].name) == 0) && (tongxunlu[i].flag == 0) && (tongxunlu[j].flag == 0))//已经有标记的就不要再排
			{
				a++;
				tongxunlu[j].flag = a;
			}
		}
	}
	 optiBubbleSort(tongxunlu, cnt);//（有问题）
	 //printf("\n");
	for (i = 0; i < cnt; i++)
	{
		if (tongxunlu[i].flag == 0)
		{
			printf("%s %s", tongxunlu[i].name, tongxunlu[i].num);
		}
		else
		{
			printf("%s_%d %s", tongxunlu[i].name, tongxunlu[i].flag, tongxunlu[i].num);
		}
		printf("\n");
	}
	return 0;
	
}
	void optiBubbleSort(struct  lianxiren tongxunlu[], int cnt)
	{
		int swap_flag = 0, i, j;
		for (i = 1; i <= (cnt - 1); i++)
		{
			for (j = 0; j < (cnt - i); j++)
			{
				if (strcmp(tongxunlu[j].name, tongxunlu[j + 1].name) > 0)
				{
					swap_flag = 1;
					struct lianxiren tmp = tongxunlu[j];
					tongxunlu[j] = tongxunlu[j + 1];
					tongxunlu[j + 1] = tmp;
				}

			}
			if (swap_flag == 0)
				break;
		}
	}

/*int cnt = 0;//记录除了相同项之外真实记录的项数
	//scanf("%s", tongxunlu[0].name);
	//scanf("%s", tongxunlu[0].num);//输入第一项一定不会重复
	for (i = 0; i < n; i++)//完成结构体输入并且排除完全相同项
	{
		scanf("%s", NAME);
		scanf("%s", NUM);
		//去除相同的部分有问题
		for (j = 0; j < i; j++)//在已经输入的项中查找
		{
			if ((strcmp(NAME, tongxunlu[j].name) == 0) && (strcmp(NUM, tongxunlu[j].num) == 0))
			{
				flag = 1;
				break;//输入时发现两项都一样，不进行保存
			}
			else {
				if (flag == 1)
				{
					n--;
					i--;
					flag = 0;
				}
				cnt++;
				strcpy(tongxunlu[i].name, NAME);
				strcpy(tongxunlu[i].num, NUM);
				break;//
			}
		}

	}
	*/
