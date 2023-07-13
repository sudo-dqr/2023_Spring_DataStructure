//此程序适用于填空选择 带字母 带数字的表达式全都可以 非常炸裂
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
double  num[100];
typedef struct node2
{
	char sign;
	struct node2 *link;
}Sign,*Signptr;
int numtop=0;
Signptr signtop = NULL;
int com(char, char);
int isEmpty(Signptr signtop)
{
	return (signtop == NULL);
}
char s[200];
char str[100];
int pos = 0;
int com(char now, char top)
{
	 if (now == '*' && top == '+' || now == '*' && top == '-' || now == '/' && top == '+' || now == '/' && top == '-')	return 1;
	else if (now == '(')	return 1;
	else if (top == '(')	return 1;
	else return 0;
}
int main()
{
	int i = 0,j;
	gets(s);
	for(i=0;s[i]!='\0'; i++)
	{
		if (s[i] == ' ')
		{
			continue;
		}
		else
		{
			if (isdigit(s[i]))
			{
				str[pos] = s[i];
				pos++;
				while (isdigit(s[i + 1]))
				{
					i++;
					str[pos] = s[i];
					pos++;
				}
				str[pos] = ' ';
				pos++;
			}
            else if(isalpha(s[i])){
                str[pos++]=s[i];
            }
			else 
			{
				if (isEmpty(signtop)||com(s[i], signtop->sign))
				{//�����ջ
					Signptr q = (Signptr)malloc(sizeof(Sign));
					q->sign = s[i];
					q->link = NULL;
					if (signtop == NULL)
					{
						signtop = q;
					}
					else
					{
						q->link = signtop;
						signtop = q;
					}
				}
				else
				{
					if (s[i] == ')')
					{
						while (signtop->sign != '(')
						{
							str[pos] = signtop->sign;
							pos++;
							signtop = signtop->link;
							if (signtop == NULL)
							{
								break;
							}
						}
						signtop = signtop->link;
					}
					else
					{
						while (signtop != NULL)
						{
							str[pos] = signtop->sign;
							pos++;
							signtop = signtop->link;
							if (signtop==NULL)
							{
								break;
							}
							else if (com(s[i], signtop->sign))
							{
								break;
							}
						}
						Signptr q = (Signptr)malloc(sizeof(Sign));
						q->sign = s[i];
						q->link = NULL;
						if (signtop == NULL)
						{
							signtop = q;
						}
						else
						{
							q->link = signtop;
							signtop = q;
						}
					}
				}
			}
		}
		
	}
	Signptr l = signtop;
	while (l != NULL)
	{
		str[pos] = l->sign;
		pos++;
		l = l->link;
	}
	printf("%s", str);
	return 0;
}