#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
对操作的撤销要通过栈来实现
1 pos str 插入字符串
2 pos n 删除n个字符
3 撤销插入或删除操作，不能撤销“撤销”操作
对于同一个时间段的撤销操作选择不入栈，而是将此时的栈顶元素退栈
*/
#define M 502
char s[3000];
typedef struct node1//记录已经发生操作的栈
{
	int op;//存储操作
	int pos;//进行操作的位置
	char add[520];//1->插入的字符串
	char delete[520];//2->删除的字符串
	struct node1* link;
}stacked,*stackedptr;
typedef struct node2//记录将要发生操作的栈
{
	int op;
	int pos;
	char add[520];
	int length;//删除长度
	struct node2* pre;
	struct node2* link;
}stacking,*stackingptr;
stackedptr stackedtop;
stackingptr stackingtop;
int flag = 0;//记录将要发生操作栈中有多少1，2
int main()
{
	int n, i, op;
	gets(s);
	scanf("%d", &n);
	//用栈结构
	for (i = 1; i <= n; i++)//已经发生过的操作,这里op==2时录入被删除的字符串
	{
		scanf("%d", &op);
		if (op == 1)
		{
			stackedptr p = (stackedptr)malloc(sizeof(stacked));
			if (p == NULL) {
				scanf("%d %s", &(p->pos), p->add);
				continue;
			}
			p->op = op;
			p->link = NULL;
			if (stackedtop == NULL)
			{
				stackedtop = p;
			}
			else
			{
				p->link = stackedtop;
				stackedtop = p;
			}
			scanf("%d %s",&(p->pos),p->add);
		}
		else if (op == 2)
		{
			stackedptr p = (stackedptr)malloc(sizeof(stacked));
			if (p == NULL) {
				scanf("%d %s", &(p->pos), p->delete);
				continue;
			}
			p->op = op;
			p->link = NULL;
			if (stackedtop == NULL)
			{
				stackedtop = p;
			}
			else
			{
				p->link = stackedtop;
				stackedtop = p;
			}
			scanf("%d %s", &(p->pos), p->delete);
		}
		else   //这里出现撤销操作就当前一步操作没发生过，将栈顶元素退栈
		{
			if (stackedtop == NULL)
			{
				continue;
			}
			else
			{
				stackedtop = stackedtop->link;
			}
		}
	}
	int cnt = n;
	//将要发生的操作  2存储删除长度
	scanf("%d", &op);
	stackingptr now = (stackingptr)malloc(sizeof(stacking));
	now=stackingtop;
	while (op != -1)
	{
		if (op == 1)
		{
			flag++;
			stackingptr q = (stackingptr)malloc(sizeof(stacking));
			q->op = op;
			q->link = NULL;
			if (stackingtop == NULL)
			{
				stackingtop = q;
			}
			else
			{
				q->pre = now;
				now->link = q;
			}
			now = q;
			scanf("%d %s", &(q->pos), q->add);

		}
		else if (op == 2)
		{
			flag++;
			stackingptr q = (stackingptr)malloc(sizeof(stacking));
			if (q == NULL) {
				scanf("%d %d", &(q->pos), &(q->length));
				continue;
			}
			q->op = op;
			q->link = NULL;
			if (stackingtop == NULL)
			{
				stackingtop = q;
			}
			else
			{
				q->pre = now;
				now->link = q;
			}
			now = q;
			scanf("%d %d", &(q->pos), &(q->length));
		}
		else  //撤销操作 如果撤销的操作是前一段输入中已经发生过的操作，就要对字符串进行改变，如果是这一段中就先进行抵消
		{
			
			if (flag>0)
			{
				flag--;
				if (flag == 0)
				{
					stackingtop = NULL;
					now = stackingtop;
				}
				else
				{
					stackingptr tmp;
					tmp = now->pre;
					now->pre->link = NULL;
					now = tmp;
				}
			}
			else//撤销的是已经完成的操作
			{
				if (cnt == 0)
				{
					scanf("%d", &op);
					continue;
				}
				else
				{
					if (stackedtop->op == 1)
					{
						char sub[5000];
						int len = strlen(stackedtop->add);
						strcpy(sub, s + stackedtop->pos + len);
						strcpy(s + stackedtop->pos, sub);
						stackedtop = stackedtop->link;
					}
					else if (stackedtop->op == 2)
					{
						char sub[5000];
						strcpy(sub, s + stackedtop->pos);
						strcpy(s + stackedtop->pos, stackedtop->delete);
						int len = strlen(stackedtop->delete);
						strcpy(s + stackedtop->pos + len, sub);
						stackedtop = stackedtop->link;
					}
					cnt--;
				}
			}
		}
		scanf("%d", &op);
	}
	stackingptr q = stackingtop;
	while (q != NULL)
	{
		if (q->op == 1)
		{
			if (q->pos == strlen(s)-1)
			{
				strcat(s, q->add);
			}
			else
			{
				char sub[5000];
				strcpy(sub, s + q->pos);
				strcpy(s + q->pos, q->add);
				strcpy(s + q->pos + strlen(q->add), sub);
			}
		}
		else
		{
			if (q->pos + q->length > strlen(s))
			{
				int i;
				for (i = q->pos; i < strlen(s); i++)
				{
					s[i] = 0;
				}
			}
			else
			{
				char sub[5000];
				strcpy(sub, s + q->length + q->pos);
				strcpy(s + q->pos, sub);
			}
		}
		q = q->link;
	}
	printf("%s", s);
	return 0;
}