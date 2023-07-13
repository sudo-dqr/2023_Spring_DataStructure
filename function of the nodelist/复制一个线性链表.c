#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
typedef struct ListNode
{
   int val;
   struct ListNode *next;	
}list,listptr;
listptr copy(listptr lista)
{
	listptr listb=NULL;
	if(lista==NULL)
	{
		return NULL;
	}
	else
	{
		listb=(listptr)malloc(sizeof(list));
		listb->val=lista->val;
		listb->next=copy(lista->next);
	}
	return listb;
}
int main()
{

  return 0;
}

