#define _CRT_SECURE_NO_WARNINGS 1
/*
链表是一种物理存储单元上非连续、非顺序的存储结构
线性表的缺点在于每一次插入和删除元素，大量元素的移动导致时间效率底下
链式结构存储的特点是用一组任意的存储单元来存储线性表中的元素，在插入和删除元素时，通过修改指针完成操作
但是因为链式存储结构的存储单元不连续，需要指针来访问后继元素
存储元素信息的域称为数据域，存储后继位置的域称为指针域，这两个部分构成一个节点
n个节点构成一个链表，即为线性表的链式存储结构
单链表：每个节点只有一个指针域 
一.链表的创建
在链表的创建中，添加指向下一个节点的指针，这个指针保存下一个结点的地址
typedef struct node* LinkList;
struct Node
{
	Elemtype data;
	struct Node* next;
};
二.链表的初始化
1.参数的传入：涉及改变链表操作的统统用指针传链表
2.创建头节点，为头节点分配内存
3.头结点指针初始化为空指针
void InitList(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(struct Node));
	(*L) ->next = NULL;
}
三.判断链表是否为空
链表头节点指针域不为空证明链表不为空，反之链表为空
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Elemtype int
typedef struct node
{
	Elemtype data;
	struct node* link;//指向下一个链结点的指针
}LNode,*LinkList;
//1.建立一个线性链表
/*
list 称为头结点指针或外指针，标明线性链表的首地址(第一个链结点的地址)
当链表为空时有  list = NULL; 可以通过list对链表进行遍历
*/
LinkList CREAT(int n)
{
	LinkList p, r, list = NULL;//定义三个指向结构体类型的指针
	Elemtype a;
	int i;
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a);//获取一个数据元素
		p = (LinkList)malloc(sizeof(LNode));//申请一个新的链结点
		p->data = a;
		p->link = NULL;//链表末尾指针域置空
		if (list == NULL)//如果链表为空
		{
			list = p;//首地址赋值给头结点指针
		}
		else
			r->link = p;//新结点连接在链表尾部
		r = p;//指针r总是指向链表末尾
	}
	return list;
}
//该算法时间复杂度为O(n),n为线性表长度

//2.求线性表的长度(O(n))
int LENGTH(LinkList list)
{
	LinkList p = list;
	int n = 0;
	while (p != NULL)
	{
		n++;
		p = p->link;//将p不断后移;  p->link p指向链结点中指针域内容，存放下一个链结点地址
	}
	return n;
}
//求长度递归解法
int LENGTH(LinkList list)//最初传入为头节点地址
{
	if (list != NULL)
	{
		return 1 + LENGTH(list->link);//下一个链结点位置
	}
	else
		return 0;
}

//3.测试链表是否为空
int ISEMPTY(LinkList list)
{
	return (list == NULL);
}
//在判断带有头节点的链表是否为空时(判断头结点的指针域是否为空)
int ISEMPTY(LinkList list)
{
	return (list->link == NULL);
}


//4.确定元素item在链表中的位置
/*
从链表的第一个位置开始向后依次比对当前链结点数据域内容是否与item匹配
查找成功返回链结点地址，查找失败返回NULL
*/
LinkList FIND(LinkList list, Elemtype item)
{
	LinkList p = list;
	while (p != NULL && p->data != item)
	{
		p = p->link;
	}
	return p;
}

//从这里开始所有的函数参数都存在传参隐患，指针传入形参并不会改变真实链表，在书中采取加& LinkList &list形式，但是C语言编译器不允许
// 解决办法为传入二级指针，对二级指针进行一层解引用，得到实际参数的地址,从而可以对原链表进行修改
// 以第一个为例，其他修改方式相似
//5.在非空线性链表的第一个链结点前插入一个数据信息为item的链结点
void INSERTLINK1(LinkList list, Elemtype item)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	p->link = list;//新节点指针域指向原表的第一个元素
	list = p;//头结点指针改向
}
//修改后
void INSERTLINK1(struct node** list, Elemtype item)//(LinkList * list , Elemtype item);也可以
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	p->link = *list;
	*list = p;
}

//6.在非空线性链表的末尾插入一个数据信息为item的链结点
void INSERTLINK2(LinkList list, Elemtype item)
{
	LinkList p,r;
	r = list;
	while (r->link != NULL)//从头向尾遍历
	{
		r = r->link;
	}
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	p->link = NULL;
	r->link = p;
}

//7.在由指针q指出的链结点后面插入一个数据信息为item的链结点
void INSERTLINK3(LinkList list,LinkList q, Elemtype item)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	if (list == NULL)
	{
		list = p;
		p->link = NULL;
	}
	else
	{
		p->link = q->link;
		q->link = p;
	}
}

//8.在线性表第i个节点后面插入一个数据信息为item的链结点
int INSERTLINK4(LinkList list, int i, Elemtype item)
{
	LinkList p, q = list;
	int j = 1;
	while (j < i && q != NULL)
	{
		q = q->link;
		j++;
	}
	if (j != i || q == NULL)
	{
		printf("链表中不存在第%d个结点\n", i);
		return -1;
	}
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	p->link = q->link;
	q->link = p;
	return 1;
}
//9.在按值有序链结的线性链表中插入一个数据信息为item的链结点
/*
假设链结点按照数值域信息从小到大排列
则插入新元素后仍然要保持为有序链表
*/
void INSERTLINK5(LinkList list, Elemtype item)
{
	LinkList p, q, r;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = item;
	if (list == NULL || item < list->data)//链表为空或数据小于第一个结点的数据域，放在第一个
	{
		p ->link = list;
		list = p;
	}
	else
	{
		q = list;
		while (q != NULL && item >= q->data)//寻找插入位置
		{
			q = q->link;
			r = q;//r指向的地址等同于q指向的地址，即指向同一个链结点
		}
		p->link = q->link;
		r->link = p;
	}
}

//10.从非空线性表中删除q所指的链结点
/*(1).删除节点是链表的第一个节点
   使外指针list指向第二个元素即可
   (2).删除点q不是第一个结点并且已知删除节点q的前驱r
   r->link=q->link;
   (3).删除点q不是第一个节点并且不知道前驱
   遍历从前向后找到q,
   停止遍历的条件为 x->link=q;
*/
//针对(1)与(2)
void DELETELINK1(LinkList list, LinkList q, LinkList r)
{
	if (q == list)
	{
		list = q->link;
	}
	else
	{
		r->link = q->link;
	}
	free(q);//已经不是链表的一部分，进行释放
}
//针对(3)
void DELETELINK2(LinkList list, LinkList q)
{
	if (q == list)
	{
		list = q->link;
	}
	else
	{
		LinkList tmp = list;
		while (tmp->link!= NULL && tmp->link != q)//这里如果写成tmp!=NULL就完了，tmp已经越过链表,链表结束的标志为指针域中的之阵位空
		{
			tmp = tmp->link;
		}
		if (tmp->link != NULL)//排除退出循环的第一种条件，只能因为下一个元素是q退出循环
		{
			tmp->link = q->link;
		}
	}
	free(q);
}

//11.销毁一个链表
//将链表中所有链结点删除(遍历链表进行删除)
void DELETELIST(LinkList *list)
{
	LinkList p = *list;//得到指向头结点的指针
	while (p != NULL)
	{
		*list = p->link;
		free(p);
		p = *list;
	}
}

//12.删除线性链表中数据值域为item的所有链结点
//从第二个开始进行判断，最后判断第一个
void DELETELIST(struct node** list, int item)
{
	struct node* LIST = *(list);//对二级指针解引用,得到外指针
	struct node* p, *q = LIST;
	p = LIST->link;//指向第二个节点
	while (p != NULL)
	{
		if (p->data == item)//满足条件
		{
			q->link = p->link;//链接p下一个结点
			free(p);//释放
			p = q->link;
		}
		else
		{
			q = p;
			p = p->link;
		}
		if (LIST->data == item)
		{
			p = LIST;
			LIST = LIST->link;
			free(p);
		}
	}
}
//13.逆转一个线性表
//改变链结点内指针域指向的方式
void INVERT(struct node** list)
{
	struct node* LIST = *list;
	struct node* p, * q, * r;
	p = LIST;
	q = NULL;
	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	LIST = q;
}

//14.将两个非空线性表连接成一个线性表
void CONNECT(struct node* lista, struct node* listb)
{
	struct node* p;
	for (p = lista; p->link != NULL; p = p->link);
	p->link = listb;
}

//15.将两个按值有序链接的非空线性表合并为一个按值链接的线性表（从小到大排列）
//设合并后链表的外指针listc
struct node* MERGELIST(struct node* lista, struct node* listb)
{
	struct node* listc,*p=lista,*q=listb,*r;
	//确定c链表头节点
	if (lista->data <= listb->data)
	{
		listc = lista;
		r = lista;
		p = lista->link;//头节点选择a的头节点，p后移一位
	}
	else
	{
		listc = listb;
		r = listb;
		q = listb->link;//头节点选择b的头节点，q后移一位
	}
	//r是什么作用？r指向listc中最后一个节点
	while (p != NULL && q != NULL)
	{
		if (p->data <= q->data)//选取p所指结点
		{
			r->link = p;     //将p所指结点连接到r之后
			r = p;           //r指向listc中最后一个节点
			p = p->link;
		}
		else
		{
			r->link = q;
			r = q;           
			q = q->link;
		}
	}
	//退出程序时说明lista或listb到头
	//这时r->link中存储的如果是p,就说明是lista到头，是q同理
	(r->link = p) ? p : q;//插入剩余节点
	//对于赋值语句判断真假，赋值语句的真值即为右值，这里如果p为空指针，判断语句为假，r->link=q;
	//如果p不是空指针，说明p还没有读完，r->link=p;
	return listc;//返回合并后链表第一个结点的值
}

//16.复制一个线性链表
struct node* COPY(struct node* lista)
{
	struct node* listb;
	if (!lista)
	{
		return NULL;
	}
	else
	{
		listb = (struct node*)malloc(sizeof(struct node));
		listb->data = lista->data;
		listb->link = COPY(lista->link);
	}
	return listb;
}

//.17利用线性链表进行数据排序
void linksort(Elemtype A[], int n)
{
	struct node* p, * list = NULL;
	int i;
	for (i = 0; i < n; i++)
	{
		INSERTLINK5(list, A[i]);//创建有序链表
	}
	p = list;
	i = 0;
	while (p != NULL)
	{
		A[i++] = p->data;
		p = p->link;
	}
}
/*
循环链表
最后链结点的指针域不再存放NULL,而是指向链表的第一个链结点
头节点与链表中其他链结点的构造相同，但是数据域可以不存放信息，也可以存放一些线性表长度之类的信息，
指针域存放第一个元素的链结点
*/