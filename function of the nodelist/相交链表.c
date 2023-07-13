#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
/*
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
*/
struct ListNode
{
   int val;
   struct ListNode *next;	
};
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    struct ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}


//或
typedef struct ListNode ListNode;

//判断两单链表是否有相交 并返回相交结点（相交->结点地址开始相同）

//双指针法：

//想法1：从两链表最后一个结点向前比较即可-->？单链表无法向前逆推 故PASS
//想法2：先遍历求得两单链表长度，让指向长链表的指针先走（长度差）步，开始遍历两指针
//返回相同结点即可

int ListSize(ListNode* head)  //求链表长度函数
{
    ListNode* p = head;
    int size = 0;
    while(p)
    {
        size++;
        p = p->next;
    }
    return size;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    ListNode* cur1 = headA;
    ListNode* cur2 = headB;

    int sizeA = ListSize(headA);
    int sizeB = ListSize(headB);
    int step = 0;
    if(sizeA > sizeB)
    {
        step = sizeA - sizeB;
        while(step--)
        {
            cur1 = cur1->next;
        }
    }
    else
    {
        step = sizeB - sizeA;
        while(step--)
        {
            cur2 = cur2->next;
        }
    }

    //开始指针遍历
    while(cur1)
    {
        if(cur1 == cur2) //若两指针指向的地址相同 说明指向的结点就是相交结点
        {
            return cur1;
        }
        else //若两指针指向不同 依次向下
        {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
    }

    return NULL;
}

