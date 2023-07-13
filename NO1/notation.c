#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
char num[101];
int main()
{
  scanf("%s",num);
  int cnt=0,jishu0=0,i,j;
  char *point=strchr(num,'.');
  int dis=point - num;
  int a=0,remember;
  for(i=0;i<=dis;i++)
  {
  	if(num[i]=='0')
  	a++;
  }
  if(a==dis)
  {
  	while(num[++dis]=='0')//ɾ��0
  	{
  		cnt++;
	  }
	int main=num[dis]-'0';
	cnt++;
	for(i = dis;i <strlen(num);i++)
	{
		if(num[i]=='0')
		{
			jishu0++;
		}
	}
	if(jishu0==strlen(num)-1-dis)
	{
		printf("%de-%d",main,cnt);
		
	}
	else
	{
		printf("%d.",main);
		i=strlen(num)-1;
		while(num[i]=='0')
		{
			i--;
		}
		for(j = dis+1;j<=i;j++)
		{
			printf("%c",num[j]);
		}
		printf("e-%d",cnt);
	}
	
}
  
   else
   {
   	int main=num[0]-'0';
   	i=strlen(num)-1;
   	num[dis]='0'; 
		while(num[i]=='0')
		{
			i--;
		}
	if(i==0)
	{
		printf("%de%d",main,dis-1);
	}
	else
	{
		printf("%d.",main);
		for(j=1;j<=i;j++)
		{
			if(j==dis)
			continue;
			else
			printf("%c",num[j]);
		}
		printf("e%d",dis-1);
	}
   }
  return 0;
}

