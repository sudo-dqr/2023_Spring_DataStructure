#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node
{ 
    int data;
    struct node *link;
}Node,*Nodeptr;
//创建链表
Nodeptr createnode(int data)
{
    Nodeptr p=(Nodeptr)malloc(sizeof(Node));
    p->data=data;
    p->link=NULL;
    return p;
}
Nodeptr createlist()
{
    Nodeptr list=NULL;
    Nodeptr p,q;
    int data;
    while(scanf("%d",&data)!=EOF)
    {
        q=createnode(data);
        if(list==NULL)
            list=p=q;
        else
        p->link=q;
        p=q;
    }
   //循环链表加上这一句 p->link=list;
    return list;
}

//链表遍历输出（循环或非循环）
void printlist(Nodeptr list)
{
    Nodeptr p=list;
    do
    {
        if(p==NULL)
        break;
        printf("%d ",p->data);
        p=p->link;
    } while (p!=list);
}


//求链表长度
//1.单向链表
int getlength1(Nodeptr list)
{
    Nodeptr p;
    int length=0;
    for(p=list;p!=NULL;p=p->link)
    length++;
    return length;
}
//2.循环链表
int getlength2(Nodeptr list)
{
    Nodeptr p;
    int length=0;
    for(p=list;p!=NULL||p!=list;p=p->link)
    length++;
    return length;
}

//查询链表中值为某个元素的结点
Nodeptr searchnode(Nodeptr list,int item)
{
    Nodeptr p=list;
    while(p!=NULL&&p->data!=item)
    p=p->link;
    return p;
}


//插入  返回list时用list接受
//在链表的第一个结点前插入新节点
//调用时：list=insertfirst(list,item)
Nodeptr insertfirst(Nodeptr list,int data)
{
    Nodeptr p=createnode(data);
    p->link=list;
    return p;
}
//在结点p后插入新节点 数据为item
Nodeptr insertnode(Nodeptr list,Nodeptr p,int item)
{
   Nodeptr q=createnode(item);
   if(p==NULL)//p为空表示插在第一个结点前面
   list=insertfirst(list,item);
   else
   {
      q->link=p->link;
      p->link=q;
   }
   return list;//注意list=insertlist(list,p,item);
}
//在链表最后插入新节点
Nodeptr insertlast(Nodeptr list,int item)
{
    Nodeptr p=createnode(item);
    if(list==NULL)
    list=p;
    else
    {
        for(p=list;p->link!=NULL;p=p->link);
        list=insertnode(list,p,item);
    }
    return list;
}
//在特定值后面插入新节点,没找到就插入到最后
Nodeptr insertdatanode(Nodeptr list,int data,int item)
{
    Nodeptr p=searchnode(list,data);//查询某个值
    if(p!=NULL)
    list=insertnode(list,p,item);
    else{
       list=insertlast(list,item);
    }
    return list;
}
//在有序链表中相应节点后面插入
Nodeptr insertsortnode(Nodeptr list,int item)
{
    Nodeptr p,q;
    for(p=list;p!=NULL&&item>p->data;q=p,p=p->link);
    if(p==list)
    list=insertfirst(list,item);
    else{
        list=insertnode(list,q,item);
    }
    return list;
}

//删除
//删除某个节点后面的节点
Nodeptr deletenextnode(Nodeptr list,Nodeptr r)
{
    Nodeptr p;
    if(r!=NULL&&r->link!=NULL)
    {
        p=r->link;
        r->link=p->link;
    }
    return list;
}
//删除指定节点p
Nodeptr deletenode(Nodeptr list,Nodeptr p)
{
    Nodeptr prep;
    if((list==NULL)||(p==NULL))
    return list;
    if(p==list)
    list=list->link;
    else{
        for(prep=list;prep!=NULL&&prep->link!=p;prep=prep->link);
        if(prep!=NULL)
        list=deletenextnode(list,prep);
    }
    return list;
}
//删除包含某一元素的节点
Nodeptr deletedatanode(Nodeptr list,int item)
{
    if(list==NULL)
    return list;
    Nodeptr p;
    for(p=list;p!=NULL&&p->data!=item;p=p->link);
    deletenode(list,p);
    return list;
}


int main()
{
    Nodeptr list=createlist();
    list=deletedatanode(list,5);
    printlist(list);
    return 0;
}