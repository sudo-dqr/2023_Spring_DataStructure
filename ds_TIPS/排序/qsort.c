//���ź��� qsort
 /*
 ������ͷ�ļ� stdlib.h 
 ����ԭ��Ϊ void qsort(void *,size_t,size_t,int(*)(const void *,const void *))
 1.��һ������Ϊ�����������׵�ַ������ֱ���������������������ָ�������ָ��
 2.�ڶ�������Ϊ���鳤�ȣ�(������Ԫ�ظ���)
 3.������Ԫ��Ϊ����Ԫ����ռ�ֽ�
 4.���ĸ�����Ϊ�����ú�����ָ�룬����ֱ��д������ 
 ��������д���� 
 
 */
//当cmp函数返回值为正数时，前一个参数指向的元素最终会在后一个参数指向的元素后面
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
//����ʵ����Ϊ��������
//��������
int cmp(const void *a,const void *b)
{
	return *(int *)a-*(int *)b;
 } 
//double��
//��������������᷵��һ��������������������������С��һ�������޷�ʵ��
//�ʲ���ֱ�ӱȽϴ�С�ķ�ʽ 
int cmp(const void *a,const void *b)
{
	return *(double *)a>*(double *)b ? 1:-1;
 } 
//�ַ�����
int cmp(const void *a,const void *b)
{
	return *(char *)a-*(char *)b;
 } 
 //�ַ�������(����������)
 
int cmp(const void *a,const void *b)
{
	return strlen((char *)a)>strlen((char *)b) ? 1:-1;
 } 
 //�ַ�������(���ֵ�������)
 int cmp(const void *a,const void *b)
 {
 	return(strcmp((char *)a,(char *)b));
  } 
//�ṹ��༶����
struct node
{
	double one;
	int two;
 } a[100];
 //1.һ������ 
int cmp(const void *a,const void *b)
{
	return (*(struct node *)a).one>(*(struct node*)b).one;
}
//2.��������
int cmp(const void *a,const void *b)
{
	if((*(struct node *)a).one!=(*(struct node *)b).one)
	return (*(struct node *)a).one>(*(struct node*)b).one? 1:-1;//doubleֱ�ӱȴ�С 
	else
	return(*(struct node*)a).two-(*(struct node *)b).two; 
 } 
int main()
{

  return 0;
}

