//快慢指针法
//设置两个快慢指针一起从链表头结点遍历
//快指针每次循环走两步，满指针每次一步
//当快指针走到链表尾部时，慢指针指向的结点即为中点

typedef struct ListNode ListNode;
struct ListNode* middleNode(struct ListNode* head)
{
    ListNode* slow = head;  
    ListNode* fast = head;
    while(fast && fast->next)  //注意这两个判定条件的前后顺序不能变
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
