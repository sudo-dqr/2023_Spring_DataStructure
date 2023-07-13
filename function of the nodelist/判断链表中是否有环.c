#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
struct ListNode
{
    int val;
    struct ListNode* next;
};
int hasCycle(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return 0;
        }
        slow = slow->next;//慢一步
        fast = fast->next->next;//快两步
    }
    return 1;
}
/*
此种判环方法中用到了快慢指针的思想，龟兔赛跑法(flyod判圈法)
快指针会在跑圈过程中追上慢指针
*/
