
typedef struct ListNode
{
	int val;
	struct ListNode* link;
}list,*listptr;
listptr deleteDuplicates(listptr head)
{
	listptr p = head;
	while (p != NULL)
	{
		if (p->link == NULL)//对应于一个元素的情况
		{
			return head;
		}
		else
		{
			if (p->val == p->link->val)
			{
				p->link = p->link->link;
			}
			else
			{
				p = p->link;
			}
		}
	}
	return head;
}
