int isPalindrome(struct ListNode* head) {
    int vals[50001], vals_num = 0;
    while (head != NULL) {
        vals[vals_num++] = head->val;
        head = head->next;
    }
    for (int i = 0, j = vals_num - 1; i < j; ++i, --j) {
        if (vals[i] != vals[j]) {
            return 0;
        }
    }
    return 1;
}
思路是先将链表转换到数组中存储


2.快慢指针法
bool需要引用头文件#include<stdbool.h>
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    while (curr != NULL) {
        struct ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

struct ListNode* endOfFirstHalf(struct ListNode* head) {
    struct ListNode* fast = head;
    struct ListNode* slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

bool isPalindrome(struct ListNode* head) {
    if (head == NULL) {
        return true;
    }

    // 找到前半部分链表的尾节点并反转后半部分链表
    struct ListNode* firstHalfEnd = endOfFirstHalf(head);
    struct ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

    // 判断是否回文
    struct ListNode* p1 = head;
    struct ListNode* p2 = secondHalfStart;
    bool result = true;
    while (result && p2 != NULL) {
        if (p1->val != p2->val) {
            result = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // 还原链表并返回结果
    firstHalfEnd->next = reverseList(secondHalfStart);
    return result;
}

