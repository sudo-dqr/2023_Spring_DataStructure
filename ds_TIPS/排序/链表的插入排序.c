#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
typedef struct ListNode
{
   int val;
   struct ListNode * next;	
}ListNode;
struct ListNode* insertionSortList(struct ListNode* head){
    //空或者只有一个节点
    if(!head || !(head->next))
        return head;

    //设置哨兵位
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->next = head;
    //有序区间的尾节点
    ListNode* lastSorted = head;
    //待排序的节点
    ListNode* cur = head->next;
    while(cur)
    {
        //待排序的节点正好和有序区间尾节点构成有序
        if(lastSorted->val <= cur->val)
        {
            lastSorted = cur;
            cur = cur->next;
        }
        else  // cur->val < lastSorted->val
        {
            ListNode* pre = dummy;
            //寻找合适的插入位置
            while(pre->next->val <= cur->val)  // 取不取等均可
                pre = pre->next;
            //插入待排序的节点
            lastSorted->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            
            cur = lastSorted->next;
        }
    }

    head = dummy->next;
    free(dummy);
    dummy = NULL;
    return head;
}

int main()
{

  return 0;
}

