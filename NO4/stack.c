#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#define M 100
typedef struct node
{
	int data;
	struct node* link;
}Node,*Nodeptr;
int isEmpty(Nodeptr);
int isFULL(int );
int main()
{
	int op,num;
	Nodeptr top = NULL;;
	int cnt = 0;
	scanf("%d", &op);
	while (op != -1)
	{
		if (1 == op)
		{
			if (isFULL(cnt))
			{
				printf("error ");
			}
			else
			{
				cnt++;
				scanf("%d", &num);
				Nodeptr p = (Nodeptr)malloc(sizeof(Node));
				p->data = num;
				p->link = NULL;
				if (top == NULL)
				{
					top = p;
				}
				else
				{
					p->link = top;
				}
				top = p;
			}
		}
		if (0 == op)
		{
			if (isEmpty(top))
			{
				printf("error ");
			}
			else
			{
				printf("%d ", top->data);
				top = top->link;
			}
		}
		scanf("%d",&op);
	}
	return 0;
}
int isEmpty(Nodeptr top)
{
	return (top == NULL);
}
int isFULL(int cnt)
{
	return (cnt == M);
}