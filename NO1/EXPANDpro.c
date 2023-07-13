#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
int legal(char s[],int i)
{
    if(isdigit(s[i-1])&&(isdigit(s[i+1]))&&(s[i+1]>s[i-1]+1))
	return 1;
	else if(islower(s[i-1])&&(islower(s[i+1]))&&(s[i+1]>s[i-1]+1))
	return 1;
	else if(isupper(s[i-1])&&(isupper(s[i+1]))&&(s[i+1]>s[i-1]+1))
	return 1;
	else return 0;
}
char s[100];
int main()
{
    gets(s);
	int i=0;
	for(i=0;i<strlen(s);i++)
	{
		if(s[i]=='-')
		{
			if(legal(s,i))
			{
               int a=s[i+1]-s[i-1];
			   int j=1;
			   for(j=1;j<a;j++)
			   {
				printf("%c",s[i-1]+j);
			   }
			}
			else
			{
				printf("-");
			}
		}
		else
		{
			printf("%c",s[i]);
		}
	}
    return 0;
}