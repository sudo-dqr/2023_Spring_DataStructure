#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
char str[320];
int flag[126];
typedef struct letter
{
	char letter;
	struct letter* link;
}LETTER, * PLETTER;
typedef struct code
{
	char letter;
	char code;
	struct code* link;
}CODE, * PCODE;
int main()
{
	gets(str);//原来的错误是用fgets读入 但是评测数据不一定会有'\n'
	int i;
	PLETTER list = (PLETTER)malloc(sizeof(LETTER)), r = list, p;
	list->letter = 0;
	for (i = 0; i < strlen(str) ; i++)
	{
		if (flag[str[i] - ' '] == 0)
		{
			if (list->letter == 0)
			{
				list->letter = str[i];
				list->link = NULL;
			}
			else
			{
				p = (PLETTER)malloc(sizeof(LETTER));
				p->letter = str[i];
				p->link = NULL;
				r->link = p;
				r = r->link;
			}
			flag[str[i] - ' '] = 1;
		}
	}
	for (i = 0; i <= 94; i++)
	{
		if (flag[i] == 0)
		{
			PLETTER q = (PLETTER)malloc(sizeof(LETTER));
			q->letter = ' ' + i;
			q->link = NULL;
			r->link = q;
			r = r->link;
		}
	}
	r->link = list;
	PLETTER flag = list;
	PLETTER pre = r;
	int length = 95;
	PCODE codelist = (PCODE)malloc(sizeof(CODE)),x, y = codelist;
	int tmp = 0;
	while (length)
	{
		int dis = flag->letter, i;
		 x = (PCODE)malloc(sizeof(CODE));//创建新节点
		x->letter = flag->letter;
		x->link = NULL;
		pre->link = flag->link;//end没动,删除节点
		length--;
		flag = flag->link;
		for (i = 1; i <dis; i++)
		{
			flag = flag->link;
			pre = pre->link;
		}
		x->code = flag->letter;
		if (tmp == 0)
		{
			tmp = 1;
			codelist->letter = x->letter;//？ 
			codelist->code = flag->letter;
			codelist->link = NULL;
		}
		else
		{
			y->link = x;
			y = y->link;
		}
	}
	x->code = list->letter;
	PCODE k=codelist;
	while(k!=NULL)
	{
		printf("%c %c\n",k->letter,k->code);
		k=k->link;
	}
	FILE* RSTREAM = fopen("in.txt", "r");
	FILE* WSTREAM = fopen("in_crpyt.txt", "w");
	PCODE ptr = codelist;
	char ch;
	while ((ch = fgetc(RSTREAM)) != EOF)
	{
		if (ch >= 32 && ch <= 126)
		{
			ptr = codelist;
			while (ptr->letter != ch && ptr != NULL)
			{
				ptr = ptr->link;
			}
			fputc(ptr->code, WSTREAM);
		}
		else fputc(ch, WSTREAM);
	}
	fclose(RSTREAM);
	fclose(WSTREAM);
	return 0;
}





