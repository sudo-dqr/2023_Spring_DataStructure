#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
struct line 
{
  int x1;
  int y1;
  int x2;
  int y2;
};
struct line a[100];
int cmp(const void *a, const void *b)
{
	return (*(struct line*)a).x1>(*(struct line* )b).x1 ? 1:-1;
}
/*
算法思路是先将输入的所有线段进行排序
左端点升序排列，这样在进行遍历时只需要正常遍历即得到从从左向右连的效果
对于每一条线段进行遍历，即对每一条线段，遍历排在他后面的线段，看看是否能够向右连 
*/
int main()
{
  int n,i,j;
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
  	scanf("%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
  }
  qsort(a,n,sizeof(struct line),cmp);//按x排序 从左向右连 
  int length=1;//记录当前长度
  int max=1;//记录最长长度 
  int max_x,max_y;
  int now=0;
  for(i=0;i<n;i++)
  {
  	now=i;
  	length=1;
  	for(j=now+1;j<n;j++)//向右链接 
  	{
  		if(a[now].x2==a[j].x1&&a[now].y2==a[j].y1)
  		{
  			length++;
  			now=j;
		  }
	  }
	  if(length>max)
	  {
	  	max=length;
	  	max_x=a[i].x1;
	  	max_y=a[i].y1;
	  }
  }
  printf("%d %d %d",max,max_x,max_y);
  return 0;
}

