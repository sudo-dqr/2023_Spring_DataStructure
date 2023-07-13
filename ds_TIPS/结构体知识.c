#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#define MAXTITL  100
#define MAXAUTL  100
//先定义一个结构体
typedef struct
{
	char name[20];
	float maxscore;
	float midscore;
}stu;
struct book
{
	char name[20];
	char author[20];
	float price;
}
void Average(stu *s)//返回类型为结构体 
{
	s->maxscore=50;
	s->midscore=50;
}
int main()
{
	stu s1={"duqirong",100,98};
	printf("%f\n",(s1.maxscore+s1.midscore)/2);
	Average(&s1);
	printf("%f\n",(s1.maxscore+s1.midscore)/2);
	return 0;
}
/*
选择填空题中出现的知识——结构体
结构体将不同类型的数据存放在一起，作为一个整体处理
例如在处理一个学生的信息，学号(字符串)，姓名(字符串)，年龄(整形)等等
结构体变量进一步加强了表示数据的能力
一.结构体声明
 struct book
{
	char title [MAXTITL];//字符串表示题目 
	char author[MAXAUTL];//字符串表示作者 
	flaot value;//浮点型表示价格 
};      //注意分号不能少，结构体也相当于一条语句 
声明描述了一个由两个字符数组和一个float变量组成的结构体
注意：他并没有创建一个实际的数据对象，而是描述了一个组成这类对象的元素
struct book library 计算机才会为其分配内存空间 
结构体声明：
1.首先使用关键字（struct）,表示接下来是一个结构体
2.后面是一个可选的标志(book)，它是用来引用该结构体的快速标记
我们以后可以这样创建数据对象
struct book library;//把library设为一个可以使用book结构体的结构体变量 
则library就包含了book结构体中的所有元素
3.花括号中结构体成员列表
成员可以使用任何一种数据类型甚至是其他的结构体
4.花括号后的分号表示结构体设计定义的结束
  
  
二.结构体的作用域
结构体声明在任何函数的外面 ，则可选标记可以在本文件中
该声明之后的所有函数都可以使用，声明在某个函数内部，则只能在内部使用，并且在声明之后
 struct book
{
	char title [MAXTITL];//字符串表示题目 
	char author[MAXAUTL];//字符串表示作者 
	float value;//浮点型表示价格 
};//注意分号不能少，结构体也相当于一条语句 
int main()
{
	struct book s1={//结构体初始化 s1引用book结构体 
		"yuwen",
		"guojiajiaoyu",
		22.5
	};
	printf("%s",s1.title);//访问结构体变量元素 
   return 0;
}
注意：结构体声明过程中各个数据类型之间以分号隔开，结构体初始化过程中是以逗号隔开
 访问结构体变量元素，结构体的名字 . 变量名字 
struct book的作用就像 int ,代表了一种数据类型
struct s1,s2,*ss;
定义了两个struct book类型的结构体变量，还定义了一个指向该结构体的指针
结构体定义
struct book library ;
等效于
struct book{
char ...
...
...
}library;

三.可选标志符可以省略的情况
1.直接创建结构体变量，而不是声明结构体类型
 struct
{
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
}library;
这样做的缺点是只能使用一次，不可复用
2.typedef(暂时掠过)
 、
 
四.结构体的初始化
用花括号括起来，用逗号分隔初始化项目列表
初始化项目与初始化的结构体成员类型相匹配
在定义结构体变量的时候没有初始化，后面就不能一起初始化 
//在定义时初始化 
struct book s1={//结构体初始化 
		"yuwen",
		"guojiajiaoyu",
		22.5
	};
//定义时未初始化
	struct book s2;
	 s2={
	"shuxue",
	"jilinjiaoyu",
	199.0
	};
这种赋值方式是错误的，定义时未初始化
后来只能对单个变量赋值
如  s2.value=22.5;	
     strcpy(s2.title,"shuxue");
     注意给字符串单个赋值不能使用=
	 s2.title="shuxue"错误
	 要使用strcpy函数 
	 
对于结构体的指定初始化(只存在于c99编译器)
 struct book s1={//结构体初始化 
	  .value=16.9
	  .title="yuwen",
	  .author="guojiajiaoyu",
		22.5
	};
可以不严格按照成员列表顺序初始化
输出值为22.5，以最后的赋值为准	
实践证明在数据结构要求的.c文件中无法实现 

访问结构体成员
结构体变量名.成员名   .称为成员运算符 
 .的运算符优先级高于&(.运算符优先级是最高的)
 scanf("%d",&s1.age); 便于理解的考虑下   可以写成scanf("%d",&(s1.age));
  
  若结构体的成员本身又是结构体
  可以通过多次使用成员运算符.实现数据访问
  变量名.子成员.下一级子成员.下下一级...... 
  struct date
{
    int year;
    int month;
    int day;
};
struct student
{
    char name[10];
    struct date birthday;
}student1;
//若想引用student的出生年月日，可表示为；student.brithday.year；
brithday是student的成员；year是brithday的成员；

五.整体与分开
1.可以将一个结构体变量作为一个整体赋值给另一相同类型的结构体变量
每个成员变量的值都将全部整体赋值给另外一个变量
2.不能将结构体变量作为一个整体进行输入和输出；
在输入输出结构体数据时，必须指明结构体变量的各成员
 struct date
{
	int year;
	int month;
	int day;
};
struct student
{
	char name[10];
	struct date birthday;//结构体的嵌套 
};
int main()
{
	struct student student1={
		"dqremperor",
		2004,
		9,  //对嵌套的结构体赋值 
		3,
	};
	struct student student2;
	student2 = student1;//结构体的整体赋值 
	printf("%s %d %d %d\n",student1.name,student1.birthday.year,student1.birthday.month,student1.birthday.day);
	printf("%s %d %d %d\n",student2.name,student2.birthday.year,student2.birthday.month,student2.birthday.day);
	return 0;
}
可以看出1.嵌套结构体中，内层结构体与外层结构体一同赋值
但是编写嵌套结构体的时候一定要注意：结构体在定义后才会生效
在母结构体中引用子结构体时，一定要确保子结构体已经在母结构体之前声明
    2.输入输出时指名结构体各个成员

六.结构体数组
之前book类型的结构体
struct book book1
{
   char name[10];
   char author[10];
   int price;
}
struct book理解为book类型的struct(结构体)
如果要记录很多本书呢？
结构体数组！
 
 6.1声明结构体数组
 struct book library[10];
 struct book为数组元素类型，library为数组名
 [10]为申请了10个struct book 单元的内存
 library为一个具体10个元素的数组，每个元素都是
 book类型的结构，library[0],library[1]...都是单独独立的book结构
 
 6.2结构体数组初始化
 struct student 
{
	char name[10];
	int age;
	int num;
};
int main()
{
	struct student array[3]={
		{
			"duqirong",
			18,
			18,
		},
		{
			"fengyuqing",
			18,
			19,
		},
		{
			"guomiao",
			18,
			20,
		}
			};
	int i;
	for(i=0;i<3;i++)
	{
		printf("第%d个学生的信息：姓名：%s，年龄：%d,学号：%d\n",i+1,array[i].name,array[i].age,array[i].num);
	}
	return 0;
} 
访问结构体数组的成员
library[2].title[5],第三个结构体的第六个字符 
array[0].age;

七.指向结构体的指针
struct +结构体名+*+指针名
struct student *dqr;  //指向student类型结构体的指针变量dqr;
dqr= &student1[0];//指向结构体数组的第一个元素
使用指针获得结构体数组元素中的成员
//方法1：引入一个运算符  ->
->用于结构体指针访问成员
. 用于结构体名访问成员
因为指针已经指向了一个结构体元素，若想要访问该结构体中的某个元素
写成 ptr->name即可 也可以写成  dqr[0].name;
//方法二：利用&与*是互逆的运算符
 (*ptr).name 因为.的优先级最高，注意加括号
  
 
八.向函数传递结构体信息
8.1传递结构体成员
结构体成员是具有单值的数据类型，就可以把他作为参数传递给一个接受这个特定参数类型的函数
这个只能实现访问，不能修改
8.2使用结构体地址
typedef struct 
{
	char name[20];
	float maxscore;
	float midscore;
}stu;//把结构体重新命名为stu
int Average(const stu * s)//使用指针接受
{
	return (s->maxscore + s->midscore)/2;
 } 
int main()
{
	stu s1={"duqirong",100,95};
	int average=Average(&s1);
	printf("%d",average);
	return 0;
}
3.使用结构体作为参数传递 
int Average(stu  s)//使用结构体接受
{
	return (s.maxscore + s.midscore)/2;
 } 
int main()
{
	stu s1={"duqirong",100,95};
	int average=Average(s1);
	printf("%d",average);
	return 0;
}
用结构体作为参数传递只是原来结构体的副本
要想调用函数修改实参结构体变量的值，只能传递地址，通过指针修改

如 int Average(const stu * s)//使用指针接受,但是使用const修饰限制修改，不会改变结构体中数据的值 
{
	return (s->maxscore + s->midscore)/2;
 } 
 int Average(stu  s)//使用结构体接受
{
	return (s.maxscore + s.midscore)/2;
 } 
 原理上，在调用这个函数的时候，会根据stu模板创建一个自动变量s，
 让后将原来s1的值赋值给他，相当于s是s1的副本
 因此只能访问无法修改，因为修改只能是修改形参的值
 ，对实参无影响，要想修改实参的值，只能传递地址，并且指针不能被const修饰
 4.结构体为参数，修改结构体并且返回类型也为结构体
 可以达到修改的目的
stu Average(stu s)//返回类型为结构体 
{
	printf("%f\n",(s.maxscore+s.midscore)/2);
	s.maxscore=50;
	s.midscore=0;
	return s;
}
int main()
{
	stu s1={"duqirong",100,98};
	stu s2=Average(s1);
	printf("%f\n",(s2.maxscore+s2.midscore)/2);
	printf("%f\n",(s1.maxscore+s1.midscore)/2);
	return 0;
}
4.传递地址，使用结构体指针接受，用于修改，不适用const进行限制
 void Average(stu *s)//返回类型为结构体 
{
	s->maxscore=50;
	s->midscore=50;
}


九.尽量使用字符数组存储字符串
 struct book
{
	char name[20];
	char author[20];
	float price;
}

补充
struct tag
{
 member-list 
}variavble-list;

struct 是结构体关键字 
tag是结构体类型名，又称为结构体的标志
struct tag 为用户定义的结构类型 
member-list 为结构体成员列表
variable-list 为结构体的变量名
 
*/

