/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode ListNode;

ListNode* reverseList(struct ListNode* head)
{
    ListNode* cur = head;
    ListNode* prev = NULL;
    while(cur)
    {
        ListNode* next = cur->next; //先保留cur结点的next指向
        cur->next = prev;  //反转cur的next指向
        prev = cur; //更新prev
        cur = next;  //更新cur
    }
    return prev;
}
