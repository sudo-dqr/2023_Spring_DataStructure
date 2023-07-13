//关于怎样设计swap函数才能真正实现数值交换 
/*
函数的传参分为值传递和地址传递，地址传递通常会改变实参
地址传递其实也是传递值，只不过传递的值是一个地址
相当于是门牌号，而地址中的变量是房间中住的人
形式参数在函数调用完成后就会销毁，形参实例化之后是实参的拷贝

1.无效函数1，本质上是改变了形式参数的值
 void swap(int p1,int p2)
{
	int t=p1;
	p1=p2;
	p2=t;
}
将传入的形式参数进行交换，对主函数中的实际参数没有影响
2.无效函数2
使用指针进行地址传递 
void swap2(int *p1,int *p2)
{
	int *t=p1;
	p1=p2;
	p2=t;
}
指针p1与指针p2的指向确实发生了改变
但是只是改变了p1和p2的地址指向
实际上a,b并没有改变,这是因为没有解引用，没能去到a,b的存储单元去
3.有效函数，使用指针且解引用
 void swap2(int *p1,int *p2)
{
	int t=*p1;
	*p1=*p2;
	*p2=t;
}


*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
void swap2(int *p1,int *p2)
{
	int t=*p1;
	*p1=*p2;
	*p2=t;
}
int main()
{
	int a=10,b=20;
	swap2(&a,&b);
	printf("%d %d",a,b);
	return 0;
}
