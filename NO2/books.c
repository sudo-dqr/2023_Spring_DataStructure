#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
1.录入 2.查找 3.删除 0.退出程序
执行过程中可以多次进行1，2，3，直到输入0
书名按字典序从小到大排列
原始图书信息无序！原始图书信息不超过500
*/
int cnt;
struct book
{
	char name[50];
	char author[20];
	char press[30];
	int year;
};
struct book bookshelf[500] = { 0 };//构建起一个书架
int flag[500];
void booksort(struct book[], int);//图书排序函数（name字典序）
int main()
{
	int op, j, i = 0, cnt = 0;//cnt
	char str[120] = "";
	FILE* Rstream = fopen("books.txt", "r");
	while (fgets(str, 120, Rstream) != NULL)//将初始文件读入结构体
	{
		sscanf(str, "%s %s %s %d", bookshelf[cnt].name, bookshelf[cnt].author, bookshelf[cnt].press, &bookshelf[cnt].year);
		cnt++;
	}
	fclose(Rstream);

	scanf("%d", &op);
	while (op != 0)//输入0关闭程序
	{
		if (1 == op)
		{
			scanf("%s %s %s %d", bookshelf[cnt].name, bookshelf[cnt].author, bookshelf[cnt].press, &bookshelf[cnt].year);
			cnt++;
			booksort(bookshelf, cnt );//在结构体数组中排好序
		}
		if (2 == op)
		{
			char word[50] = "";
			booksort(bookshelf, cnt);
			scanf("%s", word);
			for (j = 0; j < cnt; j++)
			{
				if (strstr(bookshelf[j].name, word) != NULL)
				{
					printf("%-50s%-20s%-30s%-10d\n", bookshelf[j].name, bookshelf[j].author, bookshelf[j].press, bookshelf[j].year);
				}
			}
		}
		if (3 == op)
		{
			char word[50] = "";
			scanf("%s", word);
			for (j = 0; j < cnt; j++)
			{
				if (strstr(bookshelf[j].name, word) != NULL)
				{
					flag[j] = 1;
				}
			}
		}
		scanf("%d", &op);
	}
	FILE* Wstream = fopen("ordered.txt", "w");
	for (i = 0; i < cnt; i++)
	{
		if (flag[i] == 0)
		{
			fprintf(Wstream,"%-50s%-20s%-30s%-10d\n", bookshelf[i].name, bookshelf[i].author, bookshelf[i].press, bookshelf[i].year);
		}
	}
		fclose(Wstream);
	return 0;
}
void booksort(struct book bookshelf[], int n)//图书排序函数
{
	int swap_flag = 0;
	struct book tmp;
	int i, j;
	for (i = 1; i <= (n - 1); i++)
	{
		for (j = 0; j < (n - i); j++)//开始输出错误是因为带等号错误
		{
			if (strcmp(bookshelf[j].name, bookshelf[j + 1].name) > 0)
			{
				swap_flag = 1;
				tmp = bookshelf[j];
				bookshelf[j] = bookshelf[j + 1];
				bookshelf[j + 1] = tmp;
			}
		}
		if (swap_flag == 0)
		{
			break;
		}
	}
}
