#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
1.ת��Ϊ��׺����ʽ
2.�����׺����ʽ(��)
�������ұ������������ž�ȡ���������ֽ��м��㣬��������������ջ
*/
double  num[100];
typedef struct node2//����ջ
{
	char sign;
	struct node2 *link;
}Sign,*Signptr;
int numtop=0;//��¼ջ��
Signptr signtop = NULL;
int com(char, char);//�Ƚ�������������ȼ�
int isEmpty(Signptr signtop)
{
	return (signtop == NULL);
}
char s[200];
char str[100];//�洢��׺����ʽ,��������֮���ÿո�ֿ�!!!!
int pos = 0;//��¼str�д洢����λ��
double op(double a, double b, char ch)
{
	if (ch == '+')
	{
		return a + b;
	}
	if (ch == '-')
	{
		return a - b;
	}
	if (ch == '*')
	{
		return a * b;
	}
	if (ch == '/')
	{
		return a/b;
	}
}
int main()
{
	int i = 0,j;
	gets(s);
	for(i=0;s[i]!='='; i++)
	{
		if (s[i] == ' ')//ȥ���ո�
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
				else//��������ȼ��ϵ�,�����Ƚϣ�ջ��Ԫ����ջ
				{
					if (s[i] == ')')
					{
						while (signtop->sign != '(')//������Ҫ��������
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
							if (signtop==NULL)//��ջ
							{
								break;
							}
							else if (com(s[i], signtop->sign))//���ȼ��ϴ�
							{
								break;
							}
						}
						Signptr q = (Signptr)malloc(sizeof(Sign));//�����ջ
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
	for (i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
		{
			if (isdigit(str[i + 1]))
			{
				int cnt = 0, sum = 0, rem = i;

				while (isdigit(str[i + 1]))
				{
					i = i + 1;
					cnt = cnt + 1;
				}
				for (j = 0; j <= cnt; j++)
				{
					sum = sum + (int)pow(10, cnt - j) * (str[rem + j] - '0');
				}
				num[numtop] = sum;
				numtop++;
			}
			else
			{
					num[numtop] = str[i] - '0';
					numtop++;
			}
		}
		else if (str[i] == ' ')
		{
			continue;
		}
		else
		{
			double a = num[numtop - 1];
			numtop--;
			double b = num[numtop - 1];
			num[numtop - 1] = op(b, a, str[i]);
		}
	}
	printf("%.2f", num[numtop-1]);
	return 0;
}
int com(char now, char top)
{
	 if (now == '*' && top == '+' || now == '*' && top == '-' || now == '/' && top == '+' || now == '/' && top == '-')
	{
		return 1;
	}
	else if (now == '(')
	{
		return 1;
	}
	else if (top == '(')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
