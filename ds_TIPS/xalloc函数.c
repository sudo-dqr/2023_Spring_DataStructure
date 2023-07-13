#define _CRT_SECURE_NO_WARNINGS 1
/*
malloc函数是动态内存分配函数，用于申请一块连续的指定大小的内存块区域，
以void*类型返回分配的内存区域地址
函数原型：
extern void * malloc(unsigned int num_bytes)
意为分配长度为num_bytes字节的内存块
函数头文件：stdlib.h 或malloc.h
分配成功则返回指向被分配内存的指针，分配失败则返回空指针NULL
重点：使用malloc开辟空间时，使用完成一定要释放空间
在使用malloc函数开辟的空间时，不要进行指针的移动，一旦移动之后可能会出现申请的空间和释放的空间大小不匹配
malloc函数使用形式：
malloc只开辟空间，不进行类型检查，在使用的时候进行类型的强转
malloc函数返回的是无类型自治镇，必须在其前面加上指针类型强制类型转换才可以使用
理解为：我开辟出你所需要大小的字节空间，至于怎么使用是你的事
指针自身=（指针类型*）malloc(sizeof(数据类型)*数据数量)
即在使用malloc函数之前需要计算使用到的字节数

free函数
作用：释放malloc函数给指针变量分配的空间
注意：使用后该指针变量一定要重新指向NULL，防止野指针
free(p);
p=NULL;

int main()
{
	int* p = NULL;
	//int n = 10;
	p = (int*)malloc(sizeof(int) * 1);
	*p = 100;
	printf("%d", *p);
	free(p);
	p = NULL;
	return 0;
}
*/
//realloc函数调正内存大小
/*
如果原空间后有足够的空间就可以直接追加，然后返回调整之后空间的起始位置
如果原空间后面没有足够的空间用来追加，realloc就会重新找一个新的内存区域，将原数据拷贝过去再追加，最后返回新空间的起始地址
用一个新的指针变量来接收realloc函数的返回值
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
int main1()
{
	int* p = (int*)calloc(10, sizeof(int));
	if (p == NULL)
	{
		printf("申请失败\n");
		return 0;
	}
	else
	{

	}
}