#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
*/
typedef struct ListNode
{
	int val;
	struct ListNode* next;
}list;

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* list3 = (struct ListNode*)malloc(sizeof(struct ListNode));//使用头节点了
    struct ListNode* p3 = list3;
    struct ListNode* head = list3;
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            p3->next = list1;
            list1 = list1->next;
            p3 = p3->next;
        }
        else {
            p3->next = list2;
            list2 = list2->next;
            p3 = p3->next;
        }
    }
    if (list1 == NULL) {
        p3->next = list2;
    }
    else {
        p3->next = list1;
    }
    return head->next;
}
