#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
int stack[200];		//函数调用总栈 
int s[200][200];
//函数调用分栈，横坐标的序号表示该函数，该行内存储的序号是该行号对应的函数内部调用的函数 
struct infor {
	char functionName[200]; //记录函数名，并赋予其一个特定编号 
}AllfunctionName[2000];
int flag = 0, top = 0, op, num = 0, fID, topp[200];//topp是栈顶数组，对应的 s (函数调用分栈) 每一行 
char fName[200];
int FindName(char* s, int len)	//赋予函数名编号的函数 
{
	int i;
	for (i = 0; i < len; i++)
		if (strcmp(s, AllfunctionName[i].functionName) == 0)//如果有，返回编号 
			return i;
	strcpy(AllfunctionName[len].functionName, s);//如果没有，则加入，并返回新的编号 
	return len;
}
int main()
{
	int i, j, k, t;
	while (flag == 0 && (scanf("%d", &op) == 1))	//如果函数调用总栈还有函数存在 
	{
		if (op == 8)
		{
			scanf("%s", fName);	//录入 
			fID = FindName(fName, num);	//获得编号 
			stack[top] = fID;	//加入总栈 
			if (top > 0)	//如果总栈里有函数 
			{
				s[stack[top - 1]][topp[stack[top - 1]]] = fID;
				//利用算法提示：当一个函数入栈时，它就是当前栈顶函数调用的一个函数。 
				topp[stack[top - 1]]++;	//分栈栈顶+1 
			}
			top++;//总栈栈顶+1 
		}
		else if (op == 0)
		{
			top--;	//总栈栈顶-1 
		}
		num++;
		if (top == 0)
			flag = 1;	//总栈为空 
	}
	//去重
	for (i = 0; i < 200; i++)
	{
		if (topp[i] > 0)	//如果某个函数存在调用关系 
		{
			for (j = 0; j < topp[i]; j++)
			{
				for (k = j + 1; k < topp[i]; k++)
				{
					if (s[i][j] == s[i][k])	//存在重复 
					{
						for (; k < topp[i]; k++)
						{
							s[i][k] = s[i][k + 1];	//覆盖去重 
						}
						topp[i]--;	//栈顶-1 
						k = j;	//回到原位准备再查（测试点3，4都是有3次以上的重复的调用） 
					}
				}
			}
		}
	}
	for (i = 0; i < 200; i++)
	{
		if (topp[i] > 0)	//如果某个函数存在调用关系 
		{
			printf("%s:", AllfunctionName[i].functionName);//输出 
			for (j = 0; j < topp[i] - 1; j++)
			{
				printf("%s,", AllfunctionName[s[i][j]].functionName);//输出 
			}
			printf("%s", AllfunctionName[s[i][j]].functionName);//输出 
			puts("");
		}
	}
	return 0;
}

