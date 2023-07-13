#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
多项式相乘  只输入非零系数项(包括指数为0)

创建两条链表代表输入的两条多项式
每个链结点中存入系数，次数，下一链结点link
*/
typedef struct list
{
	long long  xishu;
	long long  zhishu;
	struct list* link;
}LIST,*LinkList;
void LISTSORT(struct list**,int n);
void DELETE(struct list**);
int main()
{
	long long  a, b;
	char ch;
	LinkList lista = NULL;
	LinkList r=NULL;
	//输入第一个多项式
	do{
		scanf("%lld%lld%c", &a, &b, &ch);
		LinkList p = (LinkList)malloc(sizeof(LIST));
		p->xishu = a;
		p->zhishu = b;
		p->link = NULL;
		if (lista == NULL)
		{
			lista = p;
		}
		else
		{
			r->link = p;
		}
		r = p;
		
	} while (ch != '\n');
	//输入第二个多项式
	LinkList listb = NULL,t=NULL;
	do {
		scanf("%lld%lld%c", &a, &b, &ch);
		LinkList q = (LinkList)malloc(sizeof(LIST));
		q->xishu = a;
		q->zhishu = b;
		q->link = NULL;
		if (listb == NULL)
		{
			listb = q;
		}
		else
		{
			t->link = q;
		}
		t = q;
	} while (ch != '\n');
	/*
	经过检验到此为止对于两个多项式的录入是正确的
	值得注意的是，
	1.当多项式录入时，使用了do while 语句，判断条件在赋值条件之后
	这样可以保证最后一项的系数和次数正常录入又不新建下一个节点
	2.对于停止录入的判断
	读入两个数字之后的字符，分为空格和换行符两种情况；
	*/
	
	//相乘程序   lista listb
	//输入输出都是次数降序排列
	/*
	思路是先进行乘法，再进行排序；
	排序时指针域不动，比较相邻两项的数值域，
	交换数值域的值，如果数值域中次数值相同，就将系数相加，并删除一个链结点
	否则高次向前，低次向后
	*/
	LinkList listc = NULL;
	LinkList p = lista, q = listb,n=listb;
	r=listc;
	int cnt = 0;
	while (p != NULL)
	{
		int  i;
		while (q!= NULL)
		{
			//printf("%d\n", cnt);
			LinkList t = (LinkList)malloc(sizeof(LIST));
			cnt++;
			t->xishu = (p->xishu) * (q->xishu);
			t->zhishu = (p->zhishu) + (q->zhishu);
			//printf("\n%d %d\n",t->xishu,t->zhishu);
			t->link = NULL;
			if (listc == NULL)
			{
				listc = t;
			}
			else
			{
				r->link = t;
			}
			r = t;
			q = q->link;
		}//退出循环时q已经指向第二个多项式的末尾，需要进行重置
		q = listb;
		p = p->link;
	}//p指向第一个多项式的末尾
	//经过检验新的链表创建成功
	//对listc进行排序
	//printf("%d", cnt);
	LISTSORT(&listc,cnt);//排序没问题
	DELETE(&listc);
	LinkList d = listc;
	while(d!=NULL)
	{
		printf("%lld %lld ", d->xishu, d->zhishu);
		d = d->link;
	}
	return 0;
}
void LISTSORT(struct list** listc,int n)
{
	LinkList p = *listc;//p为外指针
	LinkList q = p->link;
	int i, j;
	for (i = 1; i <= (n - 1);i++)
	{
		for (p = *listc; p->link != NULL;p = p->link)
		{
			q = p->link;
			if (p->zhishu < q->zhishu)
			{
				long long  temp = 0;
				temp = p->zhishu;
				p->zhishu = q->zhishu;
				q->zhishu = temp;
				temp = p->xishu;
				p->xishu = q->xishu;
				q->xishu = temp;
			}
		}
	}
	return;
}
void DELETE(struct list** listc)//这个设计只有排序过后才生效
{
	LinkList p = *listc;
	while (p->link != NULL)
	{
		LinkList q = p->link;
		if (p->zhishu == q->zhishu)
		{
			p->xishu = p->xishu + q->xishu;
			p->link = q->link;
		}
		else
		{
			p = p->link;
		}
		if (p == NULL)
		{
			return;
		}
	}
	return;
}