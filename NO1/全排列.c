#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
//注意 n+1  n++  ++n的区别
/*如n==5时 
n+1作为表达式的值为 6，n的值仍然为5
n++作为表达式的值为5，但此时n的值变为6
++n作为表达式的值为6，此时n的值也为6； 
即作为参数时，++n与n+1有相同的效果，可以实现n值递增，n++则会出现bug 
*/ 
 
int result[20],flag[20];
void quanpailie(int ,int );
int main()
{
	int n,cnt=1;
	scanf("%d",&n);
//	quanpailie( n, cnt);
    printf("%d ",++n);
    printf("\n%d",n);
	return 0;
}
void quanpailie(int n,int cnt)//使用cnt 记录应该排列元素的深度 
{
	int j;
	if(cnt>n)//如果应该排列元素的深度大于输出长度，即排列完成 
	{
		for(j=1;j<=n;j++)
		{
			printf("%d ",result[j]);//输出排列结果 
		}
		printf("\n");
		return;
	}
	else
	{
		for(j=1;j<=n;j++)
		{
			if(flag[j]==0)//该元素还未进行排序 
			{
				result[cnt]=j;
				flag[j]=1;
				quanpailie(n,cnt+1);
				flag[j]=0;//回溯操作 
			}
		}
	}
}
