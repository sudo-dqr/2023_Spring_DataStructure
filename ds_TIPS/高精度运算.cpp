//高精度运算专题 



//高精度乘法 （全是正整数） 
#include<stdio.h>
#include<string.h>
char s1[1005],s2[1005];//存放两个大整数的字符
int int1[1005],int2[1005];//按低位到高位存放两个大整数的数组
int result[1000005];//乘积结果数组 ,按低位到高位存放
int main() {
int i,j;//循环变量
int d;//进位
int b;//存放按位乘的结果
int m;//结果数组的下标
int len_result;
//获取两个大整数
scanf("%s%s",s1,s2);
//按低位到高位存放两个大整数
int len1 = strlen(s1);
int len2 = strlen(s2);
for(i=0,j=len1-1; i < len1; i++,j--) {
int1[j]=s1[i]-'0';
}
for(i=0,j=len2-1; i<len2; i++,j--) {
int2[j]=s2[i]-'0';
}
//char字符数组长度等于对应的int字符数组长度
//模拟竖式相乘
for(i=0; i<len2; i++) {
d=0;//一开始相乘,进位为0
m=i;
for(j=0; j<len1; j++) {
b=int2[i]*int1[j]+d+result[m];
result[m]=b%10;//本位
m++;//为下一次做准备
d=b/10;//进位
}
if(d>0) { //一次相乘，最后一次的进位
result[m]=d;
}
}
//输出结果
len_result= len1 + len2;
while(result[len_result]==0&&len_result>0) { // 删除前导符0
len_result--;
}
for(i=len_result; i>=0; i--) {
printf("%d",result[i]);
}
return 0;
}



//高精度加法（只能两者全都是正数） 
#include <stdio.h>
#include <string.h>
int main()
{
	char s1[3000], s2[3000];
	scanf("%s%s", s1, s2);
	int a[3000], b[3000], c[3000];
	memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int i, j;
	for (i = 0, j = l1 - 1; i < l1; i++, j--)
	{
		a[i] = s1[j] - '0';
	}
	for (i = 0, j = l2 - 1; i < l2; i++, j--)
	{
		b[i] = s2[j] - '0';
	}
	int len = 0;
	if (l1 > l2)
	{
		len = l1;
	}
	else
	{
		len = l2;
	}
	for (i = 0; i < len; i++)
	{
		c[i] = a[i] + b[i];
	}
	for (i = 0; i < len; i++)
	{
		if (c[i] >= 10)
		{
			c[i + 1] += c[i] / 10;
			c[i] %= 10;
		}
	}
	i = 2999;
	while (c[i] == 0 && i > 0)
	{
		i--;
	}
	for (j = i; j >= 0; j--)
	{
		printf("%d", c[j]);
	}
	return 0;
} 


//高精度除法（全为正整数）
#include <stdio.h>  
#include <string.h>  
int len1,len2;  
char s1[905],s2[905];  
int re[905];  
void sub()  
{  
    int i=0,j;  
    while(1)  
    {
        if(s1[i]=='0')
        {
            i++;
        }  
        else  
        {
            j=i;  
            break;  
        }  
    }  
    for(;i<len2;i++)  
    {
        s1[i]=s1[i]-s2[i]+'0';  
    }
    for(i=len2-1;i>j;i--)            //低位开始检测是否小于0  
    {
        if(s1[i]<'0')  
        {  
            s1[i]+=10;  
            s1[i-1]--;  
        }
    }
}  
 
int main()  
{  
    int i,p;  
    scanf("%s%s",s1,s2);   
    len1=strlen(s1);  
    len2=strlen(s2);  
    if(len1<len2 || (len1==len2 && strncmp(s1,s2,len2)<0))   //如果a<b,直接输出0  
    {
        printf("0\n");   
    }
    p=0;  
    while(1)  
    {  
        re[p]=0;  
        while(strncmp(s1,s2,len2)>=0)      //一直进行减法，直到不能减为止  
        {  
            sub();  
            re[p]++;  
        }  
        p++;  
        if(len1==len2)  break;  
        for(i=len2-1;i>=0;i--)             //在s2前面补0，以便进行减法运算  
        {
            s2[i+1]=s2[i];   
        }
        s2[0]='0';  
        len2++;  
        s2[len2]='\0';  
    }  
    i=0;  
    while(1)  
    {  
        if(re[i]==0)
        {
            i++;
        }  
        else
        {
            break;  
        }
    }  
    for(;i<p;i++)
    {
        printf("%d",re[i]);  
    }
    return 0;  
} 

//高精度减法(也只能都是正整数) 
#include<stdio.h>
#include<string.h>
int main(void)
{
    int len_max,i;
    char m[999],n[999],temp[999];
    int a[999]={0},b[999]={0},c[999]={0};
    scanf("%s%s",m,n);
    if(strlen(m)>strlen(n))
        len_max=strlen(m);
    else
        len_max=strlen(n);
    if(strlen(n)>strlen(m)||(strlen(m)==strlen(n)&&strcmp(n,m)>0)){
       //使被减数大于减数，长度相同时需用函数strcmp判断大小
        strcpy(temp,m);
        strcpy(m,n);
        strcpy(n,temp);
       //交换数据
        printf("-");  //结果为负
    }
    for(i=0;i<strlen(m);i++){
        a[i]=m[strlen(m)-1-i]-'0';
    }
    for(i=0;i<strlen(n);i++){
        b[i]=n[strlen(n)-1-i]-'0';
    }
    for(i=0;i<=len_max;i++){
        c[i]=a[i]-b[i];
        if(c[i]<0){
            c[i]+=10;    //向上借位
            a[i+1]--;
        }
    }
    int flag=0;
    for(i=len_max;i>=0;i--){  //逆序打印
        if(c[i])
            flag=1;
        if(flag)
            printf("%d",c[i]);
    }
    if(!flag) printf("0");  //特判！
    return 0;
}




//阶乘 
#include<stdio.h>
int main()
{
 int a[10000] = { 1 }, i, up, c, s,n,j;
 scanf("%d", &n);
 c = 1;
 for (i = 1; i <= n; i++)
 {
  up = 0;//进位
  for (j = 0; j < c; j++)//各位乘i
  {
   s = a[j] * i + up;
   a[j] = s % 10;
   up = s / 10;
  }
  while (up)//位数加
  {
   a[c++] = up % 10;
   up /= 10;
  }
 }
 
 for (i = c - 1; i >=0 ;i--)
 {
  printf("%d", a[i]);
 }
 return 0;
}


//阶乘的和 
#include<stdio.h>
int main()
{
 int a[10000] = { 1 }, i, up, c, s,n,j;
 scanf("%d", &n);
 c = 1;
 for (i = 1; i <= n; i++)
 {
  up = 0;//进位
  for (j = 0; j < c; j++)//各位乘i
  {
   s = a[j] * i + up;
   a[j] = s % 10;
   up = s / 10;
  }
  while (up)//位数加
  {
   a[c++] = up % 10;
   up /= 10;
  }
 }
 
 for (i = c - 1; i >=0 ;i--)
 {
  printf("%d", a[i]);
 }
 return 0;
}
