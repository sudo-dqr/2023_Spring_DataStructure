#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
struct TreeNode{
    int val;
    struct TreeNode*left,*right;
};
void flatten(struct TreeNode*root) {
    struct TreeNode *list = NULL, *now = list, *p = root;
    struct TreeNode *stack[10000] = {0};
    int top = -1;
    while (p != NULL || top != -1) {
        if (p != NULL) {
            stack[++top] = p;
            if (list == NULL) {
                struct TreeNode *q = (struct TreeNode *) malloc(sizeof(struct TreeNode));
                q->val = p->val;
                q->left = q->right = NULL;
                now = q;
                list = q;
            } else {
                struct TreeNode *q = (struct TreeNode *) malloc(sizeof(struct TreeNode));
                q->val = p->val;
                q->left = q->right = NULL;
                now->right = q;
                now=q;
            }
            p = p->left;
        } else {
            p = stack[top--];
            p = p->right;
        }
    }
     struct TreeNode*x=list;
     while(x->right!=NULL){
         printf("%d,null,",x->val);
         x=x->right;
     }
     printf("%d",x->val);
}
int main()
{
    struct TreeNode* root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val=1;
    root->left=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val=2;root->left->left=root->left->right=NULL;
    root->right=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val=3;root->right->left=root->right->right=NULL;
    flatten(root);
    return 0;
}