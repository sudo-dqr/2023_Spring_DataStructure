#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXSIZE 100
//二叉树节点定义
struct tnode {
    int data;
    struct tnode *lchild,*rchild;
};
struct tnode*root=NULL;
int main()
{
    return 0;
}
/*
构造huffman树的方法:
1.对给定的权值进行排序，组成一个升序序列
2.每次取序列中的第一个元素和第二个元素及组成小二叉树，小二叉树的权重为两个节点权重之和
3.将小二叉树的权重加入序列，再次进行排序，以此类推，直到所有的元素都被用完
*/
/*
利用前序遍历和中序遍历或利用后序遍历和中序遍历进行确定二叉树的题目解法也是递归的
分叉的来看，分成子树来看，先从前序序列确定根节点，再在中序遍历中找到根节点，根节点左侧为左子树，右侧为右子树
再分别看左子树和右子树的前序遍历和中序遍历，逐渐递归缩小左子树和右子树，这里可能会出现子树为空的情况 
*/
//写在所有之前 关于二叉树最重要的是先建立起二叉树
//下面讨论建立二叉树的几种方法
/*事实上我们知道关于树的操作关键点在于对于树的遍历，因此先对二叉树的遍历进行总结
  对于树的遍历分为前序，中序，后序，层序遍历，其中前序、中序、后序遍历都可以通过递归和非递归(手搓栈)两种方式实现
*/
//牢记：前序、中序、后序遍历是对于访问子树根节点的先后区分的
void visit(struct tnode*p){
    printf("%d\n",p->data);
}
//前序遍历(递归) DLR  
void preorder(struct tnode* root)
{
    if(root!= NULL){
       visit(root);//访问子树根节点
       preorder(root->lchild);//转到左子树
       preorder(root->rchild);//转到右子树
    }
}
//前序遍历(非递归)  用栈模拟实现
void preOrder(struct tnode* root)
{
    struct tnode *stack[MAXSIZE]={0};
    int top=-1;
    struct tnode *p=root;
    while(p!=NULL||top!=-1){
        if(p!=NULL){
            stack[++top]=p;
            visit(p);//入栈时访问
            p=p->lchild;//一直向左移动
        }else{//访问到叶节点的左孩子(空)回退到叶节点，向右走,还是空，回退到上一个根节点向右走
            p=stack[top--];
            p=p->rchild;
        }
    }
}
//中序遍历(递归) LDR
void inorder(struct tnode *root)
{
    if(root!=NULL){
       inorder(root->lchild);
       visit(root);
       inorder(root->rchild);
    }
}
//中序遍历非递归实现
void inOrder(struct tnode *root)
{
    struct tnode *stack[MAXSIZE]={0},*p=root;
    int top=-1;
     while(p!=NULL||top!=-1){
        if(p!=NULL){
            stack[++top]=p;
            p=p->lchild;
        }else{
            p=stack[top--];
            visit(p);//出栈时访问
            p=p->rchild;
        }
     }
}
//后序遍历(递归)  LRD
void posorder(struct tnode *root)
{
    if(root!=NULL){
        posorder(root->lchild);
        posorder(root->rchild);
        visit(root);
    }
}
//后序遍历非递归实现 
void posOrder(struct tnode *root)
{
    struct tnode *stack[MAXSIZE],*p=root;
    int top=-1,flagStack[MAXSIZE]={0};//记录每个节点访问次数的栈
    while(p!=NULL||top!=-1){
        if(p!=NULL){//第一次访问 flag=1 入栈
            stack[++top]=p;
            flagStack[top]=1;//第一次访问
            p=p->lchild;
        }else{
            if(flagStack[top]==1){
                p=stack[top];
                flagStack[top]=2;//标记为第二次访问,取栈顶元素
                p=p->rchild;
            }else{  //第三次访问 出栈
                p=stack[top--];
                visit(p);
                p=NULL;//p置空 以便继续退栈
            }
        }
    }
}
//层序遍历  从上到下，从左到右，队列实现
void layerorder(struct tnode *root)
{
    struct tnode*queue[MAXSIZE]={0},*p;
    int front=-1,rear=0;
    if(root!=NULL){
        queue[0]=root;
        while(front<rear){
            p=queue[++front];//实际上是移动到了子树的根节点
            visit(p);
            if(p->lchild!=NULL)
              queue[++rear]=p->lchild;
            if(p->rchild!=NULL)
              queue[++rear]=p->rchild;
        }
    }
}
/*基于遍历的其他算法*/
//1.求二叉树中叶子结点的数目
int countLeaf(struct tnode *root)//递归实现
{
    if(root==NULL)return 0;
    if(root->lchild==NULL&&root->rchild==NULL)return 1;
    return countLeaf(root->lchild)+countLeaf(root->rchild);
}
//2.求二叉树的深度
int treeDepth(struct tnode *root)//递归
{
    int leftdepth=0,rightdepth=0;
    if(root==NULL)return 0;
    else{
        leftdepth=treeDepth(root->lchild);
        rightdepth=treeDepth(root->rchild);
        if(leftdepth>rightdepth)return leftdepth+1;
        else return rightdepth+1;
    }
}
int TreeDepth(struct tnode*p)//非递归
{
    struct tnode*stack1[MAXSIZE]={0};
    int stack2[MAXSIZE]={0};
    int curdepth=0,maxdepth=0,top=-1;
    if(p!=NULL){
        curdepth=1;//根节点为第一层
        do{
            while(p!=NULL){
                stack1[++top]=p;
                stack2[top]=curdepth;
                p=p->lchild;
                curdepth++;
            }
            p=stack1[top];
            curdepth=stack2[top--];
            if(p->lchild==NULL&&p->rchild==NULL)
                if(curdepth>maxdepth)maxdepth=curdepth;
                p=p->rchild;
                curdepth++;
        }while(p!=NULL||top!=-1);
    }
    return maxdepth;
}
//3.统计二叉树上节点值等于data的结点的个数
int findTnode(struct tnode*root,int data)
{
    if(root==NULL)return 0;
    if(root->data==data)return 1+findTnode(root->lchild,data)+findTnode(root->rchild,data);
    else return findTnode(root->lchild,data)+findTnode(root->rchild,data);
}
//4.求节点所在的层次
//使用后序遍历的非递归算法 遍历过程中访问到一个节点就判断是否为满足条件的节点，是，则此时堆栈中保存的元素个数+1即为层次
int layDepth(struct tnode*root,int item)
{
    struct tnode*stack1[MAXSIZE]={0},*p=root;
    int stack2[MAXSIZE]={0},flag,top=-1;
    do{
        while(p!=NULL){
            stack1[++top]=p;
            stack2[top]=0;
            p=p->lchild;
        }
        p=stack1[top];
        flag=stack2[top--];
        if(flag==0){
            stack1[++top]=p;
            stack2[top]=1;
            p=p->rchild;
        }
        else {
            if(p->data==item)return top+2;
            p=NULL;
        }
    }while(p!=NULL||top!=-1);
}
//5.二叉树的复制
struct tnode* copyTree(struct tnode *t1)
{
    struct tnode*t2=NULL;
    if(t1==NULL)return NULL;
    else{
        t2=(struct tnode*)malloc(sizeof(struct tnode));
        t2->data=t1->data;
        t2->lchild=copyTree(t1->lchild);
        t2->rchild=copyTree(t1->rchild);
    }
    return t2;
}
//6.测试二叉树是否等价
int equalTree(struct tnode *t1,struct tnode *t2)
{
    if(t1==NULL&&t2==NULL)return 1;
    if(t1!=NULL&&t2!=NULL&&t1->data==t2->data&&equalTree(t1->lchild,t2->lchild)&&equalTree(t1->rchild,t2->rchild))return 1;
    return 0;
}
//7.交换所有节点左右子树的位置  层次遍历方法
void exchangeBT(struct tnode *root)
{
    struct tnode *queue[MAXSIZE]={0},*temp=NULL,*p=root;
    int front=-1,rear=0;
    if(root!=NULL)
    {
        queue[0]=root;
        while(front<rear){
            p=queue[++front];
            temp=p->lchild;
            p->lchild=p->rchild;
            p->rchild=temp;
            if(p->lchild!=NULL)
            queue[++rear]=p->lchild;
            if(p->rchild!=NULL)
            queue[++rear]=p->rchild;
        }
    }
}
  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };
//检验完全二叉树 层次遍历
int isCompleteTree(struct TreeNode* root){
    if(!root)   return 1;
    //1.初始化
    struct TreeNode *p = NULL;
    struct TreeNode** Queue = malloc(sizeof(struct TreeNode*)*190);
    int front=-1,rear=-1;
    Queue[++rear] = root;   //根节点进队
    while(rear>front)   //层次遍历
    {
        p = Queue[++front];
        if(p)
        {       
            Queue[++rear] = p->left;      
            Queue[++rear] = p->right;           
        }
        else    //首次碰到空节点时,检查其后是否有空节点
        {
            while(rear>front)
            {
                p = Queue[++front];
                if(p)
                {
                    return 0;
                }     //若非空，则不是完全二叉树
            }        
        }
    }
    return 1;
}

//计算二叉树层平均值
int countsSize;
int sumsSize;
void dfs(struct TreeNode* root, int level, int* counts, double* sums) {
    if (root == NULL) {
        return;
    }
    if (level < sumsSize) {
        sums[level] += root->val;
        counts[level] += 1;
    } else {
        sums[sumsSize++] = (double)root->val;
        counts[countsSize++] = 1;
    }
    dfs(root->left, level + 1, counts, sums);
    dfs(root->right, level + 1, counts, sums);
}

double* averageOfLevels(struct TreeNode* root, int* returnSize) {//主函数
    countsSize = sumsSize = 0;
    int* counts = malloc(sizeof(int) * 1001);
    double* sums = malloc(sizeof(double) * 1001);
    dfs(root, 0, counts, sums);
    double* averages = malloc(sizeof(double) * 1001);
    *returnSize = sumsSize;
    for (int i = 0; i < sumsSize; i++) {
        averages[i] = sums[i] / counts[i];
    }
    return averages;//返回平均值数组
}
