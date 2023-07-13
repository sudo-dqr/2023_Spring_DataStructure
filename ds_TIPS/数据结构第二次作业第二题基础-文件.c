
/*
C语言文件的定义，如何对文件操作，文件指针，通过指针对文件进行操作

文件的定义：文件是相关信息的集合
C程序对文件的操作
1.读操作：从文件里面把文件的内容取出来，并输出到屏幕（不会改变文件的内容）
2.写操作：把一些内容往文件里面写入（会改变文件的内容）

C程序通过文件的指针并加上一些函数然后对文件进行操作
文件指针：存放文件的首地址，这个指针用来专门指向文件

定义文件指针
格式：FILE *指针名
如  FILE *pf;定义了一个只能指向文件的指针，之后要把文件的首地址赋值给该指针

给文件指针赋予初值
如何赋值:通过fopen函数对指针进行赋值
fopen功能
A.打开文件
B.同时返回所打开文件的首地址
C.该函数实际上就是地址
格式：fopen("要打开的文件名"，“打开方式”)；
说明：
1.打开方式是表明打开文件之后是要读还是要写
2.打开方式：
r:打开文件之后要read
w:打开文件之后要write，新的内容覆盖掉旧的内容
a:打开文件之后追加文件append 把新的数据加到末尾
r+:读写方式，读写位置在文件开头处
w+:读写方式，在文件存在时清空该文件
a+：读和追加方式，将数据写到文件末尾，文件不存在时创建该文件
rb:打开二进制文件进行读
wb:打开二进制文件进行写

打开的文件名路径中含义\的时候就要用\\
fopen("c:\\duqirong\\my.txt","r");
要打开的文件名即包含文件名的路径(右键文件，复制文件地址即可)

关闭文件
A：通过fopen能够打开文件，之后对文件进行操作
B：操作完之后通过 fclose(文件指针)来关闭文件

int main()
{
	FILE* fp;//定义文件指针
	fp = fopen("C:\\Users\\86132\\Desktop\\第一次数据结构作业\\example1c.c", "w");//指向具体文件
	//对文件进行操作
	fclose(fp);
	return 0;
}

4.对文件操作的函数
1）fgetc
  功能：从fp所指向的文件中读取出一个字符(r)
  格式：字符型变量=fgetc(fp);//fp为文件指针
  文件一定要以读的方式打开，之后指针会自动向后移动一个位置!!!!利用这个可以实现读取整个文件
2)fputc
  功能：从fp所指向的文件里面写入一个字符
  格式：fputc(要写入的字符，fp);
  文件一定要以写的方式打开，之后指针会自动向后移动一个位置
3）fgets
  功能：从fp所指向的文件里面读取出来一个字符串
  格式：fgets(str,n,fp);他会读出n-1个字符，留一个字符为\0
  str:存放字符串的数组  文件打开方式为r;
  经过实验发现，读取操作时，如果打开方式写成了"w",被打开的文件会被清空
4）fputs
  功能：把字符串写入到fp指向的文件当中
  格式：fputs(str,fp);

  总结：所有有关读取的操作——> "r"
  有关写入的操作——> "w"
  如果"r"错用为"w"会导致打开的文件被清空
  "w"错用为"r"对源文件无影响

5)专门对二进制文件进行操作
  A)fwrite
  功能：把一个结构体变量中的信息以二进制的形式写入到指定的文件当中
  格式：fwrite(&结构体变量名，sizeof(结构体类型)，1，fp)
  B)fread
  功能：从fp所指向的文件当中读出一条信息，存放早一个结构体变量中
  格式：fread(&结构体变量名，sizeof(结构体类型)，1，fp)
6)feof( EOF ?)
 功能：判断指向文件的指针是否指向文件的末尾
 格式：feof(文件指针)；返回1代表指向末尾，返回0代表没有指向末尾
 一般的用法：
 while(!feof(fp));

 fscanf(FILE* stream, const char* format, ...);
fprintf(FILE* stream, const char* format, ...);
第一个参数指文件流
fscanf(stdin,"%d%d",%a,%b);// FILE* stdin:标准输入文件（键盘）
fprintf(srdout,"%d",a+b);// FILE* stdout :标准输出文件(显示器)
C语言在开始时自动打开的标准文件：stdin,stdout,stderr,也是三个FILE*型的指针

freopen函数,重定向标准输入输出的函数
重定向输出：把原本输出在控制台的字符输出到指定文件路径当中
重定向输入：在指定的文件中读取，而不是读取在控制台中的输入
标准声明：FILE *freopen(const char *path,const char *mode,FILE *stream)
freopen函数包含在stdio.h中
path:文件名，用于存储输入输出的自定义文件名
mode:文件打开的模式，和freopen中的模式相同
stream一个文件，常用标准流文件
返回值：成功，返回path所指定文件的指针；失败返回NULL
只是输入输出的地方不一样其他代码正常写
freopen("in.txt", "r",stdin);
	freopen("out.txt", "w", stdout);
	int a, b;
	scanf("%d%d", &a, &b);
	printf("a=%d\n", a);
	printf("b=%d\n", b);
	printf("a+b=%d", a + b);
	fclose(stdin);
	fclose(stdout);
	return 0;

把正文中的小写字母改写为大写并存储为另一个文件
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<ctype.h>
int main()
{
	char ch;
	FILE* Rstream = fopen("in.txt", "r");
	if (Rstream != NULL)
	{
		FILE* Wstream = fopen("out.txt", "w");
		if (Wstream != NULL)
		{
			ch = getc(Rstream);
			while (!feof(Rstream))
			{
				fputc(isalpha(ch) ? toupper(ch) : ch, Wstream);
				ch = fgetc(Rstream);
			}
		}
		fclose(Rstream);
	}
	return 0;
}

while (fgets(line[input], N, stream)!=NULL)
	{
		len = strlen(line[input]);
		if (len > 0 && line[input][len - 1] == '\n')
		{
			line[input][len - 1] = '\0';
			len--;
		}
由于在空间充足时fgets函数会读入字符串末尾的换行符\n;
需要做特殊处理把\n换成\0

*/
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 100
int main1()
{
	FILE* stream;
	char* filename = "in.txt";
	char line[2][N] = { {""} };
	int input = 1, longest = 0, tmp;
	int max_len = 0, len;
	stream = fopen(filename, "r");
	if (stream == NULL)
	{
		perror("can not open file.\n");
		exit(-1);
	}
	while (fgets(line[input], N, stream)!=NULL)
	{
		len = strlen(line[input]);
		if (len > 0 && line[input][len - 1] == '\n')
		{
			line[input][len - 1] = '\0';
			len--;
		}
		if (len > max_len)
		{
			max_len = len;
			tmp = input;
			input = longest;
			longest = tmp;
		}
	}
	printf("longest line : %s\n", line[longest]);
	printf("line characters : %d\n", max_len);
	fclose(stream);
	return 0;
}