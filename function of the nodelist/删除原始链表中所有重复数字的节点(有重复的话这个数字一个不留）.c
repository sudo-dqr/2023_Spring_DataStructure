#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct ListNode
{
	int val;
	struct ListNode* next;
}ListNode;
struct ListNode* deleteDuplicates(struct ListNode* head) {
    //一、分类逻辑
    // struct ListNode* l=head;
    // struct ListNode* temp=l;
    // int flag=0;
    // while(l!=NULL){
    //     if(l->next!=NULL && l->val==l->next->val){//删除重复元素，除了第一个
    //     l->next=l->next->next;//删除l->next节点
    //     flag=1;//标记
    //     }
    //     else{
    //      if(flag==1){
    //          if(l==head){//删除头节点
    //             head=head->next;
    //             flag=0;
    //             l=head;//下一轮循环
    //          }
    //          else{//删除l节点
    //             temp->next=l->next;
    //             flag=0;
    //             l=temp;
    //          }
    //      }
    //      else{
    //        temp=l;//temp记录上一个节点
    //        l=l->next;//下一轮循环
    //      }
    //     }

    // }
    // return head;
    //二、增加dummy head
    struct ListNode* dummy = malloc(sizeof(struct ListNode));//相当于一只脚站在相同序列外边从头向后一个一个往下踹
    dummy->next = head;
    struct ListNode* l = dummy;
    while (l->next && l->next->next) {
        if (l->next->val == l->next->next->val) {
            int x = l->next->val;//记录x为重复值，l为前一个节点
            while (l->next && l->next->val == x) {
                l->next = l->next->next;//删除
            }
        }
        else {
            l = l->next;
        }
    }
    return dummy->next;
}