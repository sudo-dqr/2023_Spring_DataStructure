#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
/*
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
你应当 保留 两个分区中每个节点的初始相对位置。

思路:直观上我们只需要维护两个链表 small和large 
small链表按顺序存储所有小于x的结点
large链表按顺序存储所有大于等于x的节点
遍历完原链表之后将small与large尾受相连 
*/
typedef struct ListNode
{
	int val;
	struct ListNode *next;
}list,listptr;
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode* small = malloc(sizeof(struct ListNode));
    struct ListNode* smallHead = small;
    struct ListNode* large = malloc(sizeof(struct ListNode));
    struct ListNode* largeHead = large;
    while (head != NULL) {
        if (head->val < x) {
            small->next = head;
            small = small->next;
        } else {
            large->next = head;
            large = large->next;
        }
        head = head->next;
    }
    large->next = NULL;//因为large下一个链接的可能是一个小于x的结点 
    small->next = largeHead->next;
    return smallHead->next;
}

