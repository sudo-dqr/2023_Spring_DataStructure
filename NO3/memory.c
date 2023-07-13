#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
��ʼλ�á��鳤�ȡ�ָ����һ���ָ��
�洢λ������ѭ������
�ӵ�ַ��С�ĵ�һ�����п鿪ʼѰ��������������С�飨���ڵ�������ռ䣩
���п��С==��Ҫ��С ѡ��Ŀ��п���������Ƴ�����ǰλ�ñ�Ϊ�Ƴ��Ŀ��п�ָ�����һ���п�
���п��С>��Ҫ��С ʣ�²������ڿ���������
�����Ӧ�㷨��
�ڿ��������ҳ�������Ҫ���Ҵ�С��С�Ŀ��з���
������Ҫ����С�������򣬱�ͷ��ʼ����
Ѱַ���ܰ�������֮����ߣ�Ҫ��������֮ǰ����
����Ҫ�����ʱ��ѭ��������Ϊ��������
*/
typedef struct free
{
	int address;
	int size;
	struct free* link;
}FREE, * PFREE;
int a[100];
PFREE insertionSortlist(PFREE);
int main()
{
	int n, i, j;
	scanf("%d", &n);
	int length = n;
	PFREE list = NULL, r = NULL, p = NULL;
	for (i = 1; i <= n; i++)
	{
		p = (PFREE)malloc(sizeof(FREE));
		scanf("%d%d", &(p->address), &(p->size));
		p->link = NULL;
		if (list == NULL)
		{
			list = p;
		}
		else
		{
			r->link = p;
		}
		r = p;
	}
	p->link = list;
	i = 0;
	int tmp = 0;
	scanf("%d", &tmp);
	while (tmp != -1)
	{
		a[i] = tmp;
		i++;
		scanf("%d", &tmp);
	}
	//��Ϊ��������,ֻ��Ҫ��ĩβԪ�ص�ָ������ΪNULL
	/*
	Ȼ��Ӧ�öϿ�ԭ��������ĩβ��ָ���ڸ�ֵ��tmp����
	*/

	PFREE start, end;
	start = list;
	end = p;
	for (j = 0; j < i; j++)
	{
		end->link = NULL;
		PFREE listtmp = NULL, q = start, x = NULL;
		for (q = start; q != NULL; q = q->link)//����ʼ���Ƶ��յ�
		{
			r = (PFREE)malloc(sizeof(FREE));
			r->address = q->address;
			r->size = q->size;
			r->link = NULL;
			if (listtmp == NULL)
			{
				listtmp = r;
			}
			else
			{
				x->link = r;
			}
			x = r;
		}
		//��ԭ�����պ�
		end->link = start;
		PFREE tmp = insertionSortlist(listtmp);
		while (a[j] > tmp->size)
		{
			tmp = tmp->link;
			if (tmp == NULL)
			{
				break;
			}
		}
		if (tmp == NULL)
		{
			continue;
		}
		PFREE yuan = start, preyuan = yuan;
		while (yuan->address != tmp->address)
		{
			preyuan = yuan;
			yuan = yuan->link;
			start = start->link;
			end = end->link;
		}
		if (yuan->size == a[j])
		{
			start = start->link;//ͷָ����ƣ�βָ�벻��
			preyuan->link = yuan->link;//ɾ��ԭ������Ԫ��
			length--;
		}
		else
		{
			yuan->size = yuan->size - a[j];
		}
	}

	if (length == 1)//ͨ������length�����㷨�Ĵ�����������ֻʣ����������ʱ����ѭ�����޷�ɾ��������ͨ��length�������н��
	{
		printf("%d %d\n", start->address, start->size);
		return 0;
	}
	if (length!=1&&length>0)
	{
		p = start;
		printf("%d %d\n", p->address, p->size);
		p = p->link;
		while (p != start)
		{
			printf("%d %d\n", p->address, p->size);
			p = p->link;
		}
	}
	return 0;
}
PFREE insertionSortlist(PFREE head)//ֱ����ԭ�����Ͻ��в���,��������汾�ǵ�������
{
	//�ջ�ֻ��һ���ڵ�
	if (!head || !(head->link))
		return head;
	//�����ڱ�λ
	PFREE dummy = (PFREE)malloc(sizeof(FREE));
	dummy->link = head;
	//���������β���
	PFREE lastsorted = head;
	//������Ľ��
	PFREE cur = head->link;
	while (cur)
	{
		//������Ľ�����ú���������β��㹹������
		if (lastsorted->size <= cur->size)
		{
			lastsorted = cur;
			cur = cur->link;
		}
		else
		{
			PFREE pre = dummy;
			//Ѱ�Һ��ʵĲ���λ��
			while (pre->link->size <= cur->size)
			{
				pre = pre->link;
			}
			//���������Ľ��
			lastsorted->link = cur->link;
			cur->link = pre->link;
			pre->link = cur;


			cur = lastsorted->link;//��ʼ����һ������������
		}
	}
	head = dummy->link;
	free(dummy);
	dummy = NULL;
	return head;
}
