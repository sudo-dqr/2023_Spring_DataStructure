#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
char s[100];
void transform(char s[]);
int main()
{
	gets(s);
	transform(s);
	return 0;
}
void transform(char s[])
{
	char *p=strchr(s,'.');
	int pos=p-s;
	if(pos==1)//只可能为小数或1-9...
	{
		if(s[0]=='0')//是<1小数
		{
           int i=2;
		   int cnt=0;
		   while(s[i]=='0')
		   {
			 cnt++;
			 i++;
		   }
		   printf("%c",s[i]);
		   if(i+1<=strlen(s))
		   {
			 printf(".%s",s+i+1);
		   }
		   printf("e-%d",cnt+1);
		}
		else //<10小数 e0
		{
           printf("%se0",s);
		}
	}
	else//>10
	{
       printf("%c",s[0]);
	   int k=strlen(s)-1,j;
	   while(s[k]=='0')
	   {
		k--;
	   }
	   s[k+1]='\0';
	   if(k>0)
	   {
		printf(".");
		for(j=1;s[j]!='\0';j++)
		{
			if(s[j]!='.')
			printf("%c",s[j]);
		}
	   }
	   printf("e%d",pos-1);
	}
}