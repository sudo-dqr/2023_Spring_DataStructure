#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct tnode {
    int data;
    struct tnode*lchild,*rchild;
}BSTree,*BSTreeptr;
//需要注意的是二叉搜索树按照中序遍历得到的就是有序序列
//二叉查找树插入  （非递归）
void INSERTBST(BSTreeptr t,int item)
{
    BSTreeptr p,q;
    p=(BSTreeptr) malloc(sizeof(BSTree));
    p->data=item;p->lchild=p->lchild=NULL;
    if(t==NULL)t=p;
    else{
        q=t;
        while(1){
            if(item<q->data){
                if(q->lchild!=NULL){
                    q=q->lchild;
                }else{
                    q->lchild=p;break;
                }
            }
            else {
                if(q->rchild!=NULL){q=q->rchild;}
                else {
                    q->rchild=p;break;
                }
            }
        }
    }
}
//二叉查找树插入(递归)
void INSERTBST2(BSTreeptr t,int item)
{
    BSTreeptr p=(BSTreeptr)malloc(sizeof(BSTree));
    p->data=item,p->lchild=p->rchild=NULL;
    if(t==NULL)t=p;
    else{
        if(item<t->data)INSERTBST2(t->lchild,item);
        else INSERTBST2(t->rchild,item);
    }
}
BSTreeptr BTreeSort(int k[],int n)
{
    BSTreeptr t=NULL;
    for(int i=0;i<n;i++){
        INSERTBST(t,k[i]);
    }
}
//二叉查找树的查找
BSTreeptr SEARCHBST(BSTreeptr t,int item)
{
    BSTreeptr p=t;
    while(p!=NULL){
        if(p->data==item)return p;
        else if(item<p->data)p=p->lchild;
        else p=p->rchild;
    }
    return NULL;
}
//验证二叉查找树
int isBSTUtil(struct tnode* node, long long min, long long max)  
{  
  /* 是一颗空树 */
  if (node==NULL)  
     return 1; 
  /* 结点的值小于等于最小值，或者大于等于最大值都是不合理的，返回false */  
  if (node->data <= min || node->data >= max)  
     return 0;  
  /*否则递归地判断结点的左子树和右子树*/
  return  isBSTUtil(node->lchild, min, node->data) && isBSTUtil(node->rchild, node->data, max); 
}  
int isValidBST(struct TreeNode* root){
    return isBSTUtil(root,LONG_MIN, LONG_MAX);
}

//查找二叉查找树的第k小元素  中序遍历 存入数组 （中序遍历存入时就是有序的）
  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };
int kthSmallest(struct TreeNode* root, int k){ 
    if(root == NULL)
        return NULL;
    
    int* res = (int *)malloc(sizeof(int) * 100000); // 存储二叉树的值的数组, 申请空间尽可能大
    int *size = (int *)malloc(sizeof(int)); // 数组的下标
    *size = 0;
    Inorder(root, res, size); // 中序遍历搜索二叉树
    return res[k - 1]; // 返回第k小的元素
}
void Inorder(struct TreeNode *root, int *res, int *size){ // 中序遍历
    if(root == NULL)
        return;
    Inorder(root->left, res, size);
    res[(*size)++] = root->val;
    Inorder(root->right, res, size);
}
