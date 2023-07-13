#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
检测文件中{} （）
输出第一个检测到的不匹配的括号及行号
字符常量 如ch='('；字符串常量 如 str[]="((("；及注释中括号不应被处理
注释包括单行注释\\  多行注释
字符常量和字符串常量中不包含单引号和双引号,即第二次遇到时就说明字符串结束
引号为转义字符 使用时加\
*/

/*
注：这个解法缺失了多行注释的可能性，而我在一开始的解法中给出了多行注释的考虑，
通过设置一个变量flag=0;如果遇到'/*'就flag=1,在往后的不进行判断，直到在某一行中找到了后一半标志
这就要求在进行字符分情况处理时加入&&flag==0的条件
*/
#define M 200
struct node
{
	int top;
	char sign[2000];
	int row[2000];
};
struct node stack1, rem;//rem记录已经检查过的符号,无论对符号进行何种操作都先存入,如果能匹配的话，符号在存入时刚好匹配
char str[2000];//接收文件中读入的行
char* p1, * p2, ch;
int row = 0;
int flag = 0;//标记是否出现不匹配
int main()
{
	FILE* fp = fopen("example.c", "r");
	stack1.top = 0, rem.top = 0;
	//现存如再增加top,top指向栈顶元素的上方
	while (fgets(str, 2000, fp) != NULL)
	{
		row++;
		int length = 0;//记录每一行真正需要进行检查的长度
		p1= strstr(str, "//");
		p2 = strstr(str, "/*");
		/*
		对于注释的查找方式值得学习，我一开始使用的方式为从头到尾遍历到'\'后再判断下一个字符来判断
		把// 与  '/*'作为字符串来进行匹配更高效
		*/
		if ((p1 == NULL) && (p2 == NULL))
		{
			length = strlen(str);
		}
		else if ((p1 == NULL) && (p2 != NULL))
		{
			length = p2 - str;
		}
		else if ((p1 != NULL) && (p2 == NULL))
		{
			length = p1 - str;
		}
		else
		{
			int a = p1 - str;
			int b = p2 - str;
			if (a < b)
			{
				length = a;
			}
			else
			{
				length = b;
			}
		}
		int i;
		for (i = 0; i < length; i++)//注意！i<length,一开始的bug是因为写成了i<strlen(str);这就对注释中的内容进行了检查
		{
			if (str[i] == '(')//左括号直接入栈
			{
				stack1.sign[stack1.top] = '(';
				rem.sign[rem.top] = '(';
				stack1.row[stack1.top] = row;
				stack1.top++, rem.top++;
			}
			else if (str[i] == ')')
			{
				rem.sign[rem.top] = ')';
				rem.top++;
				if (stack1.sign[stack1.top - 1] == '(')
				{
					stack1.top--;//完成匹配进行出栈
				}
				else
				{
					ch = ')';
					flag = 1;
					break;
				}
			}
			else if (str[i] == '{')
			{
				rem.sign[rem.top] = '{';
				rem.top++;
				if (stack1.sign[stack1.top - 1] != '(')
				{
					stack1.sign[stack1.top] = '{';
					stack1.row[stack1.top] = row;
					stack1.top++;
				}
				else
				{
					ch = '(';
					flag = 1;
					break;
				}
			}
			else if (str[i] == '}')
			{
				rem.sign[rem.top] = '}';
				rem.top++;
				if (stack1.sign[stack1.top - 1] == '{')
				{
					stack1.top--;
				}
				else
				{
					ch = '}';
					flag = 1;
					break;
				}
			}
			else if (str[i] == '\'')
			{
				char *p = strchr(str + i + 1, '\'');
				if (p != NULL)
				{
					i = p - str;
				}
				else
					continue;
			}
			else if (str[i] == '\"')
			{
				char* p = strchr(str + i + 1, '\"');
				if (p != NULL)
				{
					i = p - str;
				}
				else
					continue;
			}
		}
		if (flag == 1)
		{
			if (ch == '(')
			{
				printf("without maching '%c' at line %d", ch, stack1.row[stack1.top - 1]);

			}
			else//  '{'  ')'  '}'
			{
				printf("without maching '%c' at line %d", ch, row);
			}
			break;
		}
	}
	if (flag == 0)
	{
		if (stack1.top == 0)
		{
			printf("%s", rem.sign);
		}
		else
		{
			printf("without maching '%c' at line %d", stack1.sign[stack1.top - 1], stack1.row[stack1.top - 1]);
		}
	}
	fclose(fp);
	return 0;
}
