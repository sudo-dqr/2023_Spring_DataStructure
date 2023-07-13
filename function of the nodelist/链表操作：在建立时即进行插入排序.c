/*有序插入建立链表 C语言实现*/
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct linklist
{
    int data;
    struct linklist* next;
}list, * plist;
/*按从小到大顺序插入*/
void order_insert_list(plist* head, int number)
{
    plist p_new = (plist)malloc(sizeof(list));
    plist pre = NULL;           /* pre指针作为temp指向next前的备份 */
    p_new->data = number;       /* 赋予新值给新结点 */
    p_new->next = NULL;
    plist temp = (plist)malloc(sizeof(list));
    temp = *head;  /*每次插入前从链表头开始的位置*/
    /*首位空结点赋初值*/
    if (NULL == *head)
    {
        *head = p_new;
        return;
    }
    /*若新data比头结点小，头结点前插入*/
    if (p_new->data < temp->data)
    {
        p_new->next = temp;
        *head = p_new;
        return;
    }
    else
    {
        while (NULL != temp)
        {
            if (p_new->data >= temp->data)/* 新结点对当前结点data比较 */
            {
                pre = temp;
                temp = temp->next;/*当前结点后移，直至5（比如1 2 3 5 插入4）的位置*/
                continue;
            }
            else
            {
                p_new->next = temp;/* 插入新结点 */
                pre->next = p_new; /* temp的前一个的位置的next指向新结点p_new */
                break;
            }
        }
        if (NULL == temp)/* 当temp最终为尾结点时，说明新元素data最大，将结点作为尾结点 */
        {
            p_new->next = NULL;
            pre->next = p_new;   /* temp的前一个的位置的next指向新结点p_new */
        }
    }
}
int  main()
{
    int number;
    plist head=NULL;     
    printf("input some numbers:\n");
    while (scanf("%d",&number)!=EOF)
    {
        order_insert_list(&head, number);
    }
    plist p = head;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    return 0;
}