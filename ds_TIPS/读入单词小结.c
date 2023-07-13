#define _CRT_SECURE_NO_WARNINGS 1
//1.采用二维数组方式统计单词
/*
这里需要注意的是，由于读取方式是fgetc(ch);
每读入一个字符，文件指针会自动后移一位，
注意不要跳读
注意：fgetc或fgets 返回值为成功读取的字节数，读到文件末尾时返回EOF
*/
char word[500][50];
int main()
{
	int cnt = 0;//记录单词个数
	int place = 0;//记录每个单词中读到的字母位置
	int flag = 1;//标记单词
	FILE* RSTREAM = fopen("article.txt","r");
	char ch = fgetc(RSTREAM);
	while (ch != EOF)
	{
		if (isalpha(ch))
		{
			flag = 0;
			word[cnt][place] = tolower(ch);//转换成小写字母
			place++;//单行读取位置后移
		}
		else//读入的不是字母，
		{
			if (flag != 1)//说明上一个读入的还是字母，而这一个不是字母，结束该行的录入
			{
				word[cnt][place] = '\0';
				cnt++;//开到下一行
				flag = 1;
				place = 0;
			}
			//这时候如果判断flag==1
			// 就说明上一个读取的也不是字母，不开下一行，通过flag一直等于1可以跳过中间的无用字符
		}
		ch = fgetc(RSTREAM);//读入下一个字符
	}
	fclose(RSTREAM);
}


/*
使用链表方式实现
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node
{
	char s[100];
	int num;
	struct node* next;
}Node,*Nodeptr;
Nodeptr list;
char s[1010];
char aaa[1010], * fro, * p;
char* read(char* ch, char* t, char* end)//读取单词函数
{
	while (!isalpha(*ch))//跳过非字母字符
	{
		ch++;
	}
	if (ch >= end)//无效行
	{
		return NULL;
	}
	while (isalpha(*ch))
	{
		*t = *ch;
		ch++;
		t++;
	}
	*t = 0;
	return ch;
}
Nodeptr insert(char* t)//插入函数，在插入的过程中就完成了排序和去重
{
	Nodeptr pre = list, now = list->next;
	if (now == NULL)//单词表中还没有单词
	{
		Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
		strcpy(tmp->s, t);//直接插入
		tmp->num = 1;
		tmp->next = NULL;
		list->next = tmp;
		return tmp;
	}
	//此时now的初始值为list->next;list作为头节点不存放元素
	for (; now != NULL; pre = now, now = now->next)//now=list->next!=NULL说明此时表中已经有元素
	{
		int fl = strcmp(t, now->s);
		if (fl < 0)//新插入的单词的字典序比当前指向的单词要小，插入到前端（排序）
		{
			Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
			strcpy(tmp->s, t);
			tmp->num = 1;
			tmp->next = now;//插入到前端
			pre->next = tmp;
			return tmp;
		}
		else if (fl == 0)//是相同的单词（去重）
		{
			now->num++;
			return now;
		}
	}
	//退出循环时还没插入说明字典序比已有单词任何一个都大，插入到最后
	Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
	strcpy(tmp->s, t);
	tmp->num = 1;
	tmp->next = NULL;
	pre->next = tmp;//当前pre->now指向最后一个不为空的结点，now已经指向NULL；
	return tmp;
}
int main()
{
	freopen("article.txt", "r", stdin);
	list = (Nodeptr)malloc(sizeof(Node));//创建头节点
	list->next = NULL; fro = aaa;
	while (gets(s) != NULL)//按行读入
	{
		int i;
		for (i = 0; i < strlen(s); i++)
		{
			if (isalpha(s[i]))
			{
				s[i] = tolower(s[i]);
			}
		}
		p = s;
		while (1)
		{
			p = read(p, fro, s + strlen(s));
			if (p == NULL)
			{
				break;
			}
			insert(fro);
		}
	}
	Nodeptr now = list->next;
	//输出
	while (now != NULL)
	{
		printf("%s %d\n", now->s, now->num);
		now = now->next;
	}
	return 0;
}


int getword(FILE* fp,char *w)
{
  int c;//这里把c定义为int类型比较稳定 因为c接受返回值可能有EOF即为-1，而char类型没有-1的说法
  while(!isalpha(c=fgetc(fp)))
  if(c==EOF)return c;
  else continue;
  do
{
  *w++=tolower(c);
}while(isalpha(c=fgetc(fp)));
 *w='\0';//结束符
 return 1;
}
