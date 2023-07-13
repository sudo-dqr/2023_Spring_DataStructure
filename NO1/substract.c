#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
//需要注意的是
/*
1.一开始我使用fgets进行字符串的读取
计算字符串的长度时，得到的结果会比真实值大一
这是因为fgets会读取跳到第二个字符串时的换行符 
即回车换行符被读入到第一个字符串当中 
使用gets函数或者scanf均不会出现读取换行符的情况 

2.strcmp函数的使用
 strcmp函数的误解：strcmp不是比较字符串长度的
  strcmp函数是对传入的两个字符串从第一位开始比较ASC码
  如果相同 就比较下一位 ，直到不同或遇到\0
   并不能判断字符串长短
   如arr1 : a b c d e \0
   arr2:    a b q \0
   有arr1<arr2
   对于函数原型
   int strcmp(str1,str2)
   >0 str1>str2(不一定返回1)
   =0 str1==str2
   <0  str1<str2 
 
 3.设置数组
 设置局部数组就一定要初始化为0
 要不就设置成全局数组
 局部数组的值是不确定的 
 养成良好编程习惯   直接写全局数组 
 
 4.字符数组的输入与存储顺序
  从下标为0开始输入
  输入越早下标越小 
  
  
  高精度减法的思路分析
1.由于输入的两个数字都已经超过了long long 的范围
  需要用数组进行模拟
  使用字符数组读入两个数，便于计算两个数的位数
 2. 对于两个数大小的判断
  第一步是看位数(strlen)
  当位数相同时使用strcmp(s1,s2);
  注意：！！！位数不同时不可以使用strcmp进行比较
  可能出现  长的字符串中某一位比小字符串小，造成  长<短  的情况发生 
  故比较两个数的大小步骤
  1.长度
  2.长度相同时 strcmp; 
3.区分两个数的大小，在计算中采取大减小的形式
  标记好符号
4.读入两个字符型数组时
数学上的高位存入了计算机存储中的小地址端（数组的小下标）
即这时两个数的存储是高位对齐的
如1 2 3 4 5 6
  4 5 6
  直接对应数位相减显然错误
  故将两个数组逆序过来，同时转化为int型数组
5.按位对齐计算并进行输出
  涉及到借位问题
6.把前导0删除(最后result的位数应该是与大的数相同的)
7.输出最终结果（根据标记看是否输出负号）  
*/ 

int main()
{
	char s1[81]="",s2[81]="";
     int a[101]={0},b[101]={0};
	 int result[101]={0};
	int i=0,flag=0,max_len=0;
     gets(s1);gets(s2);
     int l1=strlen(s1),l2=strlen(s2);
     if(l1<l2||l1==l2&&strcmp(s1,s2)<0)//s2 big
     {
     	flag=1;
     
     	for(i=l2-1;i>=0;i--)
     	{
     		a[l2-i-1] = s2[i]-'0';
		 }
		 for(i=l1-1;i>=0;i--)
		 {
		 	b[l1-i-1] = s1[i]-'0';
		 }
	 }
	 else{
	
	 	for(i=l1-i;i>=0;i--)
	 	{
	 		a[l1-i-1] = s1[i]-'0';
		 }
		 for(i=l2-i-1;i>=0;i--)
		 {
		 	b[l2-i-1] = s2[i]-'0';
		 }
	 }
	 if(l1>l2)
	 {
	 	max_len=l1;
	 }
	 else{
	 	max_len=l2;
	 }
	 for(i=0;i<max_len;i++)
	 {
	 	if(a[i]>=b[i])
	 	{
	 		result[i]=a[i]-b[i];
		 }
		 else{
		 	a[i+1]--;
		 	result[i]=a[i]-b[i]+10;
		 }
	 }
	 while(result[max_len-1]==0&&max_len>1)//小细节 如果结果就等于0呢？不能删没了啊 
	 {
	 	max_len--;
	 }
	 if(flag==1)
	 {
	 	printf("%c",'-');
	 }
	 for(i=max_len-1;i>=0;i--)
	 {
	 	printf("%d",result[i]);
	 }
		 return 0;
}

