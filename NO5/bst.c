#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    int height;
    struct node *lchild,*rchild;
}BTNode,*BTNodeptr;
BTNodeptr root=NULL;
void insertBST(int item)
{
     BTNodeptr p,q;
     p=(BTNodeptr)malloc(sizeof(BTNode));
     p->data=item;
     p->height=1;
     p->lchild=p->rchild=NULL;
     if(root==NULL)
     {
        root=p;
     }
     else
     {
        q=root;
        while(1)
        {
            p->height++;
            if(item<q->data)
            {
                if(q->lchild==NULL)
                {
                    q->lchild=p;
                    break;
                }
                else q=q->lchild;
            }
            else if(item>=q->data)
            {
               if(q->rchild==NULL)
               {
                q->rchild=p;
                break;
               }
               else q=q->rchild;
            }
        }
     }
}
void printBTNode(BTNodeptr t)
{
    if(t!=NULL)
    {
    printBTNode(t->lchild);
    if(t->lchild==NULL&&t->rchild==NULL)
    printf("%d %d\n",t->data,t->height);
     printBTNode(t->rchild);
    }
}
int main()
{
    int n,item,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&item);
        insertBST(item);
    }
    printBTNode(root);
    return 0;
}