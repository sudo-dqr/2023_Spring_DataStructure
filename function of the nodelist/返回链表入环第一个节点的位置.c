#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
返回入链位置(索引从0开始)
这一题相当于上一题的加强版，更加注重数学推导
下面进行推导：
假设从链表头节点到入环点的距离为a,fast与slow相遇点将圆环分成的长度分别为b,c
由速度公式 a+(b+c)*n+b=2*(a+b)（这里可以证明必定在慢指针跑完一圈之前就相遇）
           得到a= (n-1)*(b+c)+c;
        这时我们可以定义一个指针ptr指向链表的头节点
        当fast与slow相遇时，ptr开始与slow同时向后移动，二者相遇位置即为环点
*/
struct ListNode
{
    int val;
    struct ListNode* next;
};
struct ListNode* detectCycle(struct ListNode* head) {
    struct ListNode* slow = head, * fast = head;
    while (fast != NULL) {
        slow = slow->next;
        if (fast->next == NULL) {
            return NULL;
        }
        fast = fast->next->next;
        if (fast == slow) {
            struct ListNode* ptr = head;
            while (ptr != slow) {
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr;
        }
    }
    return NULL;
}
