#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
//排序的链表包含头节点，第一个节点不存放数据 
typedef struct node
{
  int data;
  struct node * link;	
}NODE ,*PNODE;
void BubbleSort(PNODE L)
{
	int i ,count = 0, num;//count记录链表结点的个数，num进行内层循环，
	NODE *p, *q, *tail;//创建三个指针，进行冒泡排序
	p = L;
	while(p->link != NULL)//计算出结点的个数
	{
		count++;//注释①
		p = p->link;
	}
	for(i = 0; i < count - 1; i++)//外层循环，跟数组冒泡排序一样
	{
		num = count - i - 1;//记录内层循环需要的次数，跟数组冒泡排序一样，
		q = L->link;//令q指向第一个结点
		p = q->link;//令p指向后一个结点
		tail = L;//让tail始终指向q前一个结点，方便交换，也方便与进行下一步操作
		while(num--)//内层循环 次数跟数组冒泡排序一样
		{
			if(q->data > p->data)//如果该结点的值大于后一个结点，则交换
			{
				q->link = p->link;
				p->link = q;
				tail->link = p;
			}
			tail = tail->link;//注释②
			q = tail->link;//注释②
			p = q->link;//注释②
		 } 
	} 
}

int main()
{
  int i,n;
  scanf("%d",&n);
 
  PNODE list=(PNODE)malloc(sizeof(NODE));//建立头指针 
  PNODE now=(PNODE)malloc(sizeof(NODE));
  list->link=NULL;
  for(i=1;i<=n;i++)
  {
  	PNODE p=(PNODE)malloc(sizeof(NODE));
  	scanf("%d",&p->data);
  	p->link=NULL;
  	if(list->link==NULL)
  	{
  		list->link=p;
	  }
	  else
	  {
	  	now->link=p;
	  }
	  now = p;
  }
  BubbleSort(list);
  PNODE q=(PNODE)malloc(sizeof(NODE));
  q=list->link;
  while(q!=NULL)
  {
  	printf("%d\n",q->data);
  	q=q->link;
  }
  return 0;
}

