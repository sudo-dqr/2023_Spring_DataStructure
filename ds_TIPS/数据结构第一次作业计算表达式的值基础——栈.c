#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
//基于数组的数据结构 栈
/*
栈在数据结构上先入后出，类似于向弹夹中压入子弹
FILO:first in last out故取元素只能取栈顶元素，不能跳过栈顶元素向下取 
对数组插入和删除元素只能在数组的尾部进行
数据放入堆栈——入栈
删除数据称为出栈，出栈，入栈都在栈顶进行
初始时栈为空栈，栈顶位置top==0,位于数组首端，当逐渐压入元素，栈顶向数组尾端移动
栈的位置比栈顶元素大一   
位于栈顶的元素称为栈顶元素 
 栈顶随着插入和删除元素改变位置 
 入栈前判断栈是否已满
 出栈或者取栈顶元素时判断栈是否已空 
*/ 
#define maxsize 100
int stack[maxsize];//定义数组作为堆栈的存储结构 
int top;//利用变量top记录栈顶位置  top==0空栈   top==maxsize 栈满 
int isStackEmpty();//判断栈是否为空 
int isStackFull();//判断栈是否已满 
void push(int );//入栈 
void pop();//出栈 
int getTop();//取栈顶元素 

int main()
{
	int i;
   for( i=1;i<=8;i++)
   {
   	if(!isStackFull())
   	 push(i);
	  }  
	while(!isStackEmpty())
	{
		printf("%d ",getTop());//取得栈顶元素 
		pop();//将栈顶后移 
	 } 
	 return 0;
}
//判断栈空
int isStackEmpty()
{
	return (0==top);
 } 
//判断栈满
int isStackFull()
{
	return maxsize==top;
 } 
//入栈
void push(int e)
{
	if(top<maxsize)
	stack[top++]=e;//栈顶的位置放入新的元素，栈顶后移
	else
	printf("StackFull!"); 
 } 
//出栈
void pop()
{
	if(top>0)//有元素
	--top;//出栈为什么只要移动栈顶就可以了？ 出栈后，原来的数据还在栈里，但是已经沦为垃圾 
	else
	printf("StackEmpty!"); 
 } 
//取栈顶元素
int getTop()
{
	if(top>0)
	return stack[top-1];//说明栈顶位于栈顶元素后
	else
	{
		printf("StackEmpty!");
		return -1;//返回值无意义
		/*
		注意：return 0  一般用在主函数结束时，表示本函数成功完成
		      return -1  一般用在子函数结尾，表示该函数失败 
		*/ 
	 } 
 } 
