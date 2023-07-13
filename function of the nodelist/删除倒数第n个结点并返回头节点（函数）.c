#include<stdio.h>
//删除链表中倒数第n个结点并返回头指针（一次遍历的做法）
struct ListNode
{
    struct ListNode* next;
};
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* ptr1 = head;
    struct ListNode* ptr2 = head;
    int i;
    for ( i = 0; i < n; i++)//ptr1先走，与ptr2形成路程差
    {
        ptr1 = ptr1->next;
        if (ptr1 == NULL)
        {
            head = head->next;
            return head;
        }
    }
    while (ptr1->next != NULL)
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    if (ptr1 == head)
    {
        head = head->next;
        free(ptr1);
        return head;
    }
    struct ListNode* p = ptr2->next;
    ptr2->next = ptr2->next->next;
    free(p);
    return head;
}
