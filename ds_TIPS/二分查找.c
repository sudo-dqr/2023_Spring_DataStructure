#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
/*
二分查找，又称折半查找，该方法是建立在元素有序的前提下的，时间复杂度为logn
限制条件： 1.序列有序  2.只查找一个元素 
*/
int main()
{
  int arr[]={1,2,3,4,5,6,7,8,9};
  int size=sizeof(arr)/sizeof(arr[0]);
  int mid=0,left=0,right=size-1;
  int k;
  scanf("%d",&k);
  int pos=0; 
  while(left<=right)
  {
  	mid=(left+right)/2;
  	if(arr[mid]<k)
  	{
  		left=mid+1;
	  }
	  else if(arr[mid]>k)
	  {
	  	right=mid-1;
	  }
	  else
	  {
	  	pos=mid;
	  	break;
	  }
  }
  if(left>right)
  {
  	printf("无");
  }
  else
  {
  	printf("yes在第 %d",pos+1);
  }
  return 0;
}
int searchword(struct lnode list[],char *w)
{//单词表升序排列 
	int low=0,high=n-1;mid=0;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(strcmp(w,list[mid].word)<0)
		{
			high=mid-1;
		}
		else if(strcmp(w,list[mid].word)>0)
		{
			low=mid+1;
		}
		else
		{
			list[mid].cnt++;//重复出现只计数
			return 0; 
		}
	}
	return insertword(list,low,w);
}
int searchElem(ElemType list[], int N, ElemType item)
{
int low = 0, high = N - 1, mid;
while (low <= high)
{
mid = (high + low) / 2;
if (item < list[mid])
high = mid – 1;
else if (item > list[mid])
low = mid + 1;
else
return (mid);
}
return -1;
}
