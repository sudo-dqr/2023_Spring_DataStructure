#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
typedef struct NTreeNode{
    int data;
    int Numchild;//记录N叉树下有多少叉  判断是否是叶子节点就是看numchild=0
    struct NTreeNode*Nchild[MAXSIZE];
}NTreeNode,*NTreeptr;
//在遍历算法中我们将遍历结果（输出顺序）保存在数组中，可以根据实际情况更改
//N叉树的遍历算法无中序
//前序遍历
void prehelper(NTreeptr t,int *pos,int *a)
{
    if(t==NULL)return ;
    a[(*pos)++]=t->data;
    for(int i=0;i<t->Numchild;i++){
        prehelper(t->Nchild[i],pos,a);
    }
}
int *preorder(NTreeptr t,int *returnsize)//returnsize记录返回数组的大小
{
    int *a=(int *)malloc(sizeof(int)*MAXSIZE);
    int pos=0;
    prehelper(t,a,&pos);
    *returnsize=pos;
    return a;
}
//后序遍历
void poshelper(NTreeptr t,int *pos,int *a)
{
    if(t==NULL)return ;
    else{
        for(int i=0;i<t->Numchild;i++){
            poshelper(t->Nchild[i],pos,a);
        }
        a[(*pos)++]=t->data;
    }
}
int *posorder(NTreeptr t,int *returnsize)
{
    int *a=(int *)malloc(sizeof(int)*MAXSIZE);
    int pos=0;
    poshelper(t,&pos,a);
    *returnsize=pos;
    return a;
}
//层序遍历  层序遍历用队列实现
//将遍历结果存入二维数组版本
#define MAX_LEVEL_SIZE 1000
#define MAX_NODE_SIZE 10000
int** levelOrder(NTreeptr root, int* returnSize, int** returnColumnSizes) {
    int ** ans = (int **)malloc(sizeof(int *) * MAX_LEVEL_SIZE);//开二维数组  一共有level行
    *returnColumnSizes = (int *)malloc(sizeof(int) * MAX_LEVEL_SIZE);
    if (!root) {
        *returnSize = 0;
        return ans;
    }
    NTreeptr * queue = (NTreeptr *)malloc(sizeof(NTreeptr) * MAX_NODE_SIZE);
    int head = 0, tail = 0;
    int level = 0;
    queue[tail++] = root;
    while (head != tail) {
        int cnt = tail - head;
        ans[level] = (int *)malloc(sizeof(int) * cnt);
        for (int i = 0; i < cnt; ++i) {
            NTreeptr cur = queue[head++];
            ans[level][i] = cur->data;
            for (int j = 0; j < cur->Numchild; j++) {
                queue[tail++] = cur->Nchild[j];
            }
        }
        (*returnColumnSizes)[level++] = cnt;
    }
    *returnSize = level;
    free(queue);
    return ans;
}
//普通版本  队列
void layerorder(NTreeptr root)
{
   NTreeptr queue[100]={NULL},p=NULL;
    int front=-1,rear=0;
   if(root!=NULL){
       queue[0]=root;
       while(front<rear){
         p=queue[++front];
         //printf("%d",p->data);//输出所有节点
         if(p->Numchild==0)//无后继分支 即为叶子节点
         {
             printf("%d",p->data);//输出叶子节点
         }else{
             for(int i=0;i<p->Numchild;i++){
                 queue[++rear]=p->Nchild[i];
             }
         }
       }
   }
}
//求N叉树深度
int maxDEPTH(NTreeptr root){
    if(root==NULL)return 0;
    int max_depth=0,max=0;
    for(int i=0;i<root->Numchild;i++){
        max= maxDEPTH(root->Nchild[i]);
        max_depth=max_depth>max?max_depth:max;
    }
    return max_depth+1;
}
int main()
{
    return 0;
}
