#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node
{
	int num;
	int needtime;
	int waittime;
	struct node* link;
}line ,*lineptr;
int group[500];//����ÿ������
int num;
lineptr front = NULL;
lineptr rear = NULL;
lineptr p, q;
int n, i, j, k, winnum = 3, windows[5];//windows����ֵֻ�洢��ǰҵ��ʣ��ʱ��
int cnt = 0;
int main()
{
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &group[i]);
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= group[i]; j++)//����һ��
		{
			cnt++;
		    p = (lineptr)malloc(sizeof(line));
			p->num = cnt;
			scanf("%d", &(p->needtime));
			p->waittime = 0;
			p->link = NULL;
			if (front == NULL)
			{
				front = p;
			}
			else
			{
				rear->link = p;
			}
			rear = p;
		}
		num = num + group[i];
		//����֮���пմ���Ҳ�����з������ж��Ƿ����Ӵ���
		while ((num >= 7 * winnum) && (winnum < 5))
		{
			winnum++;
		}
		q = front;
	    for (k = 0; k < winnum; k++)
			{
				if (windows[k] == 0&&q!=NULL)
				{
						num--;
						windows[k] = q->needtime;
						printf("%d : %d\n", q->num, q->waittime);
						front = front->link;
						q = q->link;
				}
			}
		q = front;
		while (q != NULL)
		{
			q->waittime++;
			q = q->link;
		}
		for (k = 0; k < winnum; k++)//ÿһ�μ��ٵ�ǰ����needtime
		{
			if (windows[k] > 0)//���е�һ��
			{
				windows[k]--;
			}
		}
		while ((num < 7 * winnum) && (winnum > 3))
		{
			winnum--;
		}
	}
	while (num)
	{
		q = front;
		for (k = 0; k < winnum; k++)
		{
			if (windows[k] == 0 && q != NULL)
			{
				num--;
				windows[k] = q->needtime;
				printf("%d : %d\n", q->num, q->waittime);
				front = front->link;
				q = q->link;
			}
		}
		q = front;
		while (q != NULL)
		{
			q->waittime++;
			q = q->link;
		}
		for (k = 0; k < winnum; k++)//ÿһ�μ��ٵ�ǰ����needtime
		{
			if (windows[k] > 0)//���е�һ��
			{
				windows[k]--;
			}
		}
		while ((num < 7 * winnum) && (winnum > 3))
		{
			winnum--;
		}
	}
	return 0;
}
