#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
int main()
{
 typedef int dqr;
 dqr a;
 scanf("%d",&a);
 printf("%d",a);
return 0;
}
/*
 typedef是C语言的关键字，作用为为复杂的声明定义简单的别名
用法：在传统的变量声明表达式中，用新的名字替换变量名
再把关键字typedef加在该语句的开头即可
 1.typedef为基本数据类型取别名 
 如typedef int dqr;
  dqr a;
  2.typedef为自定义数据类型取别名
   自定义的数据类型如结构体
    struct students
    {
       char sex;
       char name[120];
       int ages;
    };
    结构体重新定义数据名
	struct students
	{
	   char sex;
	   char name[20];
	   int ages;
    }std;
    std.name[20]="duqirong";
    
    或者stryct students 
	{
	   char sex;
	   char name[20];
	   int ages;
     };
     typedef struct students std;
     std.name[20]="duqirong"
*/

