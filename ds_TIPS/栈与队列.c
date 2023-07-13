#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
栈与队列都属于线性结构，是在操作上受限制的线性表，又被称为限定性数据结构
一.堆栈
只允许在表的一端进行插入和删除操作的线性表，允许操作的一端称为栈顶，栈顶元素的位置用一个称为栈顶指针的变量(top)给出
另一端称为栈底，表中没有元素的时候称为空栈
操作：入栈，出栈  先进后出，最先进入元素在栈底，最后进入元素在栈顶
堆栈是一个动态结构
堆栈的存储结构分为两种，顺序存储结构与链式存储结构
1.顺序堆栈的构造
堆栈的顺序存储结构可以用一个具有M个元素的数组 stack[0...M-1]来描述
堆栈是一个动态结构，数组是一个静态结构，利用静态结构的数组描述一个动态结构的堆栈存在着溢出问题
栈中已经有M个元素，此时再做进栈操作会发生“上溢”，对空栈进行删除产生“下溢”；（注意检测满或空）

检测栈满，栈空，入栈，出栈，取栈顶元素等操作时间复杂度都是O(1)
*/
//初始化一个堆栈
//用top标记栈顶元素的位置
/*
#define M 1000
typedef int elemtype;
elemtype stack[M];
int top;
//当堆栈为空时 top==-1;
void initial(int* top)
{
	top == -1;
}
int empty(int top)
{
	return (top == -1);
}
int full(int top)
{
	return (top == M-1);
}
int gettop(elemtype *stack, int top, int* item)//直接把栈顶元素存入item
{
	if (empty(top))
		return 0;
	else
	{
		*item = stack[top];
		return 1;
	}
}
int push(elemtype* stack, int* top, int item)
{
	if (full(top))
		return 0;
	else
	{
		stack[++(*top)] = item;
		return 1;
	}
}

删除操作中，删除只是将栈顶指针向下移一个位置，原来的栈顶元素依然存在

int pop(elemtype* stack, int* top, int* item)
{
	if (empty(top))
		return 0;
	else
	{
		item = stack[(*top)--];
		return 1;
	}
}
/*
堆栈的链式存储结构 链栈
对于链接堆栈的操作时间复杂度O(1)，优势在于在不知道具体进栈元素个数时，不会发生溢出问题

typedef struct node
{
	elemtype data;
	struct node* next;
}Node,*Nodeptr;
Nodeptr top = NULL;
int isEmpty(Nodeptr top)
{
	return (top == NULL);
}
int GetTop(Nodeptr top, int* item)
{
	if (isEmpty(top))
		return;
	else
	{
		*item = top->data;
		return 1;
	}
}
//插入相当于在最前面插入一个元素
int Push(Nodeptr* top, int item)
{
	Nodeptr p;
	if (!(p = (Nodeptr)malloc(sizeof(Node))))
		return 0;
	else
	{
		p->data = item;
		p->next = *top;
		*top = p;
		return 1;
	}
}
//删除即为删除线性链表的第一个元素
int pop(Nodeptr* top, int* item)
{
	Nodeptr p;
	if (isEmpty(*top))
		return 0;
	else
	{
		p = *top;
		item = p->data;
		*top = (*top)->next;
		free(p);
		return 1;
	}
}

堆栈的应用
一.符号匹配检查
1.创建一个空的堆栈，依次读入字符直到文件的末尾
2.读得的字符为左花括号或左圆括号，则将其压入堆栈
如果读得的字符为右花括号或右圆括号
(1).若此时堆栈为空，出现不匹配现象，报告错误
(2).若此时堆栈不为空，退出当前栈顶元素，推出的不为对应的左花括号或左圆括号，不匹配，报告错误
(3).读到文件末尾，堆栈非空，报告错误
见作业题
二.数制转换
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node {
	int num;
	struct node* next;
}Node,*Nodeptr;
int main()
{
	Nodeptr top = NULL;
	int n;
	scanf("%d", &n);
	while (n)
	{
		Nodeptr p = (Nodeptr)malloc(sizeof(Node));
		p->num = n%8;
		p->next = NULL;
		if (top == NULL)
		{
			top = p;
		}
		else
		{
			p->next = top;
			top = p;
		}
		n=(n-n%8)/8;
}
	while (top != NULL)
	{
		printf("%d", top->num);
		top = top->next;
	}
	return 0;
}
三.递归
递归调用既不节省时间啊，也不节省空间，运行效率比较低，无论是从时间角度还是空间角度都比非递归程序差
消除递归，时间大为节省 
注：程序中频繁使用的部分尽量消除递归
从递归算法到非递归算法的转换(用栈实现)
int func(int m, int n)
{
	if (m == 0 || n == 0)
		return m + n + 1;
	else
		return func(m - 1, func(m - 1, func(m, n - 1)));
}

#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
int reccurresive(int m, int n)
{
	int stack[100], top = -1;
	do
	{
		if (m * n != 0)
		{
			stack[++top] = m - 1;
			n--;
		}
		else
		{
			n = n + m + 1;
			if (top >= 0)
				m = stack[top];
			top--;
		}
	} while (top >= -1);
	return n;
}
int main()
{
	int n, m;
	scanf("%d %d", &m, &n);
	printf("%d", reccurresive(m, n));
	return 0;
}

四.表达式计算
算术表达式为中缀表达式，转换为后缀表达式进行计算
后缀表达式即运算符出现在运算对象之后，
特点为：1.表达式中无括号，也不存在运算符优先级差别，计算过程按照运算符出现次序进行
        2.运算对象先后次序相同
处理表达式时：
从左向右依次扫描后缀表达式的各个单词；
如果读到的单词为运算符，就对该运算符前面的两个运算对象施以该种运算，并将结果存入临时单元中
作为一个新的对象重复上述过程
例如：A+(B-C/D)*E
      ABCD/-E*+;

处理后缀表达式：
处理过程中设置一个堆栈，保存已经读到的运算对象，读到的若为运算对象就将其压入堆栈，
若为运算符就从堆栈中取出两个运算对象进行计算，得到的结果作为新的运算对象压入堆栈
表达式最后的结果位于top指向的栈顶

产生后缀表达式：
后缀表达式中运算对象次序完全相同，只是运算符按照某种顺序发生了改变
从左向右依次扫描，每读到一个运算对象就把他作为后缀表达式一部分输出，
处理运算符时提前建立运算符栈，每读到一个运算符就将其与栈顶位置运算符优先级进行比较
如果当前读到运算符优先级较高，则进栈，继续读下一个单词
当前读到运算符优先级较低，栈顶运算符退栈，作为后缀表达式一部分进行输出，持续比较
遇到左括号直接入栈，运算符优先级降到最低
遇到右括号进行出栈，将运算符输出到表达式中，直到遇到左括号，括号不输出到后缀表达式中
*/

/*
队列
一种只允许在表的一端进行插入操作，在另一端进行删除操作的线性表
允许插入的一端称为队尾，队尾元素的位置由一个变量rear(后方)指出，
允许删除的音段称为队头，队头元素的位置由另一个变量front指出
没有元素的队列称为空队
队列：先入先出表
*/
/*
队列顺序存储结构
用数组描述队列的顺序存储结构
一维数组 QUEUE[0..M-1];front 队头，rear 队尾
约定：front指向实际队头位置的前一个位置，rear指向实际队尾元素所在的位置
队头元素为 queue[front+1] 队尾元素为queue[rear];
测试一个队列是否为空 front==rear

插入考虑上溢，删除考虑下溢
插入操作在队尾，修改队尾指针，
删除操作在队头，修改队头指针
算法时间复杂度均为O(1)

//初始化队列
#define M 1000
void initialQ(int* front, int* rear)
{
	*front = -1;
	*rear = -1;
}
//测试队列是否为空
int isempty(int front, int rear)
{
	return (front == rear);
}
//取当前队头元素（判断当前队是否为空）
int getfront(int queue[], int front, int rear, int* item)
{
	if (isempty(front, rear))
		return 0;
	else
	{
		*item = queue[front + 1];
		return 1;
	}
}
//直到现在我才理解返回值与接口
//返回值代表着取元素的成功还是失败
//队头元素通过指针进行直接赋值，如果返回队头元素值的话，会与判断空队的返回值发生冲突，队头元素的值也可能为0
//添加
int add(int queue[], int* rear, int item)
{
	if (rear == M - 1)
	{
		return 0;
	}
	else
	{
		*(rear)++;
		queue[*(rear)] = item;
		return 1;
	}
}
//删除  队头指针向队尾方向移动一个格
int delete(int queue[],int *front,int rear,int *item)
{
	if (isempty(front, rear))
	{
		return 0;
	}
	else
	{
		*front++;
		*item = queue[*front];
		return 1;
	}

}
*/
/*
循环队列
队列操作中在队头删除，在队尾插入，队列的动态变化犹如使队列整体向右移动
当队尾指针 rear==M-1时，队列前端可能还有空闲空间
*/
#define M 1000
//循环队列插入
int addcq(int queue[], int front, int* rear, int item)
{
	if ((*rear + 1) % M == front)//循环队列已满
	{
		return 0;
	}
	else
	{
		(*rear)++;
		queue[(*rear) % M] = item;
		return 1;
	}
}

//循环队列删除
int deleteq(int queue[], int* front, int rear, int* item)
{
	if (*front == rear)//循环队列为空
		return 0;
	else
	{
		*front = (*front + 1) % M;
		*item = queue[*front];
	}
}

/*
链接队列
测试队列为空的条件  front == NULL;
除了销毁队列时间复杂度为 O(N)
其他操作均为O(1)
*/
typedef struct node
{
	int data;
	struct node* next;
}Node,*Nodeptr;
//初始化
void initialq(Nodeptr front, Nodeptr rear)
{
	front = rear = NULL;
}
//测试为空
int EMPTY(Nodeptr front)
{
	return (front == NULL);
}
//取队头元素
int gettopelem(Nodeptr front, int* item)
{
	if (EMPTY(front))
		return 0;
	else
	{
		item = front->data;
		return 1;
	}
}

//链接队列的插入
int addlink(Nodeptr front, Nodeptr rear, int item)
{
	Nodeptr p;
	if (!(p = (Nodeptr)malloc(sizeof(Node))))
		return 0;
	p->data = item;
	p->next = NULL;
	if (front == NULL)
		front = p;
	else
	{
		rear->next = p;
	}
	rear = p;
}
//链接队列删除
int deletelink(Nodeptr front, int* item)
{
	Nodeptr p;
	if (front == NULL)
		return 0;
	else
	{
		p = front;//暂存队头元素
		*item = p->data;
		front = p->next;
		free(p);
		return 1;
	}
}
//链接队列的销毁   
void DELETE(Nodeptr front, Nodeptr rear)
{
	while (front)
	{
		rear = front->next;
		free(front);
		front = rear;
	}
}
