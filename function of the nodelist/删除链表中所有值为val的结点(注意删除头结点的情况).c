#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
/*
删除链表中所有满足值为val的结点 ，并返回头指针 
这里唯一需要注意的是可能头节点被删掉了 
*/
typedef struct ListNode
{
   int val;
   struct ListNode * next;	
}list,*listptr;
struct ListNode* removeElements(struct ListNode* head,int val)
{
	listptr dummy=(listptr)malloc(sizeof(list));
	dummy->next=head;
	listptr now=dummy;
	while(now->next)
	{
		if(now->next->val==val)
		{
			now->next=now->next->next;
		}
		else
		{
			now=now->next;
		}
	}
	return dummy->next;
}
int main()
{

  return 0;
}

