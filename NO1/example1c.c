#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#define maxsize 100
char sign[maxsize];//存储运算符的栈 
int num[maxsize];//存储数字的栈 
int topnum,topsign;
char line[maxsize],sub[maxsize];
int isStackFullNum( );
int isStackEmptyNum( );
int isStackFullSign( );
int isStackEmptySign( );
void pushnum(int );
void pushsign(char );
void popnum( );
void popsign();
int getTopNum( );
char getTopSign();
int compare(char );//比较运算符优先级 
int calculate(char rela,int num1,int num2)
{
	if(rela=='*')
	{
		return num1*num2;
	}
	else if(rela=='/')
	{
		return num1/num2;
	}
	else if(rela=='+')
	{
		return num1+num2;
	}
	else 
	{
		return num1-num2;
	}
}
int main()
{
   int i,j=0,k;
   gets(line);//输入时千万记着打进去等号 
   //删除表达式中的空格 
   for(i = 0; line[i]!='=' ;i++)
   {
   	if(line[i]!=' ')
   	{
   		sub[j++]= line[i];
	   }
   }
   sub[j]='\0';
  // printf("%s\n",sub); 
   for(i = 0;sub[i]!='\0';i++)
   {
   	if(isdigit(sub[i]))
   	{
   		int cnt=0,sum=0,rem=i;
   		if(isdigit(sub[i+1]))
   		{
   			while(isdigit(sub[i+1]))
   			{
   			i=i+1;
   			cnt=cnt+1;
   		    }
   		    for(j=0;j<=cnt;j++)
		{
			sum=sum+(int)pow(10,cnt-j)*(sub[rem+j]-'0');
		}
		pushnum(sum);
		}
	    else{
	          pushnum(sub[i]-'0');
        	}
	
	   }
   //提取字符串中的数   已经成功！ 解决了12读取的问题 
	//进行符号处理   我的sub字串中是没有'='的 
	else if(sub[i]=='*'||sub[i]=='/'||sub[i]=='-'||sub[i]=='+')
	{
		if(isStackEmptySign())//符号栈为空直接插入 
		{
			pushsign(sub[i]);
			//printf("%c",sign[0]);//减号已经正确存入了啊 
		}
		else   //有问题 ,需要研究运算符 
		{
			//压入符号过程 
			if(compare(sub[i]))
			{
				pushsign(sub[i]);
			//	printf("%c",sign[1]);
			}
			else
			{
			  //如果运算符优先级不够高
			 /*
			 先拿出sign栈顶元素和num的两个栈顶元素
			 计算结果压入num成为新的栈顶元素，不断计算直到要放入的符号优先级够用
			 乘除遇加减，加减遇空栈,先进行循环模拟过程 
			 */ 
			 while(!compare(sub[i]))
			 {
			 	char op=getTopSign();
			 	popsign();
			 	int num2=getTopNum();
			 	popnum();
			 	int num1=getTopNum();
			 	popnum();
			 	//取出一个符号两个数,栈顶对应向下移动 
				pushnum(calculate(op,num1,num2)); 
				
			 }
			 pushsign(sub[i]);
			}
		}
	}
   }
  
   for(i=0;i<3;i++)
   {
   	//printf("%c",sign[i]);
   }
   //sign数组压入正确 
   
   //表达式扫描完毕
   if(isStackEmptySign())//sign数组为空 
   {
   	for(j=0;j<topnum;j++)
   	{
   		printf("%d",num[j]);
	   }
   }     //500 = 问题解决 即符号栈为空的问题解决了 
   else{
   	while(!isStackEmptySign())
   	{
   		 char op=getTopSign();
   		 popsign();
   		 int num2=getTopNum();
   		 popnum();
   		 int num1=getTopNum();
   		 popnum();
   		 pushnum(calculate(op,num1,num2));
	   }
    printf("%d",num[0]);
} 
   return 0;
}
int isStackEmptyNum()
{
	return (0==topnum);
}
int isStackFullNum()
{
	return (maxsize==topnum);
}
int isStackEmptySign()
{
	return (0==topsign);
}
int isStackFullSign()
{
	return (maxsize==topsign);
}
void pushnum(int e)
{
	if(topnum<maxsize)
	{
		num[topnum++] = e;
	}
}
void pushsign(char ch)
{
	if(topsign<maxsize)
	{
		sign[topsign++] = ch;
	}
}
void popnum()
{
	if(topnum>0)
	topnum--;
}
void popsign()
{
	if(topsign>0)
	topsign--;
}
int getTopNum()
{
	if(topnum>0)
	return num[topnum-1];
	else
	return -1;
 } 
char getTopSign()
{
	if(topsign>0)
	return sign[topsign-1];
	else
	return -1;
}
int compare(char now)//能压住的几种情况· 
{
	if(now=='*'&&sign[topsign-1]=='+'||now=='*'&&sign[topsign-1]=='-'||now=='/'&&sign[topsign-1]=='+'||now=='/'&&sign[topsign-1]=='-')
	return 1;
	else if(topsign==0)
	return 1;
	else
	return 0;
 } 

