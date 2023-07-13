#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
int flag[100];
int main()
{
   char str[100]="";
   
   fgets(str,100,stdin);
   int i=0;
   for(i=0;i<strlen(str);i++)
   {
   	if(str[i]!='-'&&flag[i]!=1)
   	{
   		printf("%c",str[i]);
   		flag[i]=1;
	   }
   	if(str[i]=='-')
   	{
   		int k=0;
		if(islower(str[i-1])&&islower(str[i+1])&&(str[i+1]-str[i-1]>1))//都是小写并且可扩展 
		{
		flag[i]=1;//进行标记
			int front = str[i-1]-'a',behind = str[i+1]-'a';
			for(k=front+1;k<=behind-1;k++)
			{
				printf("%c",'a'+k);//打印展开字符并未存在字符数组中 
			}
		 } 
		else if(isupper(str[i-1])&&isupper(str[i+1])&&(str[i+1]-str[i-1]>1))//都是大写并且可扩展 
		{
			flag[i]=1;//把紧邻的三个元素进行标记，并把-隐藏掉 
			int front = str[i-1]-'A',behind = str[i+1]-'A';
			for(k=front+1;k<=behind-1;k++)
			{
				printf("%c",'A'+k);//打印展开字符并未存在字符数组中 
			}
		 }  
		else  if(isdigit(str[i-1])&&isdigit(str[i+1])&&(str[i+1]-str[i-1]>1))//都是数字并且可扩展 
		{
			flag[i]=1;//把紧邻的三个元素进行标记，并把-隐藏掉 
			int front = str[i-1]-'0',behind = str[i+1]-'0';
			for(k=front+1;k<=behind-1;k++)
			{
				printf("%c",'0'+k);//打印展开字符并未存在字符数组中 
			}
		 } 
		 else
		 {
		 	printf("-");
		 	flag[i]=1;
		 }
   	
    } 
   }
   return 0;
}


