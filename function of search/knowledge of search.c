#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
/*
查找表：
逻辑结构：一种线性结构,
物理结构:顺序组织存储：顺序查找、折半查找
        链式组织存储：顺序查找
        索引组织存储：索引查找
        散列组织查找：散列查找
*/
//有序连续顺序表的折半查找 O(logn);
int bisearch(int key[],int n,int item)
{
    int low=0,high=n-1,mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(item==key[mid])  return mid;
        if(item>key[mid]) low=mid+1;
        else  high=mid-1;
    }
    return -1;
}
//折半查找递归实现
/*
在第一次调用的算法中 
int low=0,high=n-1;
int pos=bisearch2(key,low,high,k);
*/
int bisearch2(int key[],int low,int high,int k)
{
    int mid=0;
    if(low>high)return -1;
    else {
    mid=(low+high)/2;
    if(k==key[mid])return mid;
    else if(k>key[mid]) return bisearch2(key,mid+1,high,k);
    else return bisearch2(key,low,mid-1,k);
    }
}
/*判定树 相当于折半查找 O(logn)
在当前查找范围内居中的记录的位置作为根节点，前半部分与后半部分的记录的位置
分别构成根节点的左子树与右子树
根节点位置：mid=(low+high)/2;
成功的查找过程正好相当于走了一条从根节点到被查找结点的路径，经历的比较次数
即为该节点在二叉树中的层次数
正因为判定树可以较好地模拟折半查找的过程，我们在题目中遇到问有关折半查找次数的问题,查找路径的问题
都可以通过画出判定树的方式解决，查找一个元素的比较次数不超过树的深度，无论有还是没有这个元素
*/
//基于折半查找的插入元素
#define MAXSIZE 100
int n=0;//代表数组中元素个数
int searchElEM(int list[],int k)
{
    int low=0,high=n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(k==list[mid])return mid;
        else if(k>list[mid])low=mid+1;
        else high=mid-1;
    }
    return low;//若原表中没有查找元素，low就是需要插入的位置
}
int insertElem(int list[],int item)
{
    if(n==MAXSIZE)return -1;
    int i=0,j=0;
   // i=searchELEM(list,item);
    for(j=n-1;j>=i;j--)list[j+1]=list[j];
    n++;
    return 1;
}
/*查找函数 bsearch 包含在头文件 stdlib.h
void *bsearch(指向要查找的元素的指针，指向要检验的数组的指针，数组的元素数目，数组每个元素的字节数，比较函数)
这里的比较函数与qsort中的比较函数是一样的
*/
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
int main()
{
   int a[5]={0,1,2,3,4};
   int b=2;
   if(bsearch(&b,a,5,sizeof(a[0]),cmp)!=NULL)
   printf("1\n");
   int*p=(int *)bsearch(&b,a,5,sizeof(a[0]),cmp);
   printf("%d",p-a);
   printf("\n%d",*p);
    return 0;
}
//链表的查找
struct listnode
{
    int data;
    struct listnode*link;
};
struct listnode*search(struct listnode*list,int item)
{
    struct listnode*p=list;
    for(;p!=NULL;p=p->link)
    if(p->data==item)return p;
    return NULL;
}
//二叉查找树的查找和插入
struct tnode
{
    int data;
    struct tnode*lchild,*rchild;
};
struct tnode*searchBST(struct tnode*t,int key)
{
    struct tnode*p=t;
    while(p!=NULL)
    {
        if(key==p->data)return p;
        if(key>p->data)p=p->rchild;
        else p=p->lchild;
    }
    return NULL;
}
struct tnode*insert(struct tnode*p,int item)
{
    if(p==NULL)
    {
        p=(struct tnode*)malloc(sizeof(struct tnode));
        p->data=item;
        p->lchild=p->rchild=NULL;
    }
    else if(item<p->data)p->lchild=insert(p->lchild,item);
    else if(item>p->data)p->rchild=insert(p->rchild,item);
    else 
       //do-something for example :cnt++;
    return p;
}
//trie树（多叉树结构）
/*
键值由固定的字符序列组成 如huffman码，英文单词(26个字母)
典型应用：字典树，字典树每个内部节点都有26个子节点
树的高度为最长单词长度
*/
struct tnode{
    char isword;//有这个标记就说明到这个节点之前的路径已经组成了一个单词
    char isleaf;//标记是否为叶节点，是叶节点自然也可以形成单词
    struct tnode*ptr[26];
};
void wordTree(struct tnode*root,char *w)
{
   struct tnode*p;
   for(p=root;*w!='\0';w++){
    if(p->ptr[*w-'a']==NULL){
        p->ptr[*w-'a']=talloc();
        p->isleaf=0;
    }
    p=p->ptr[*w-'a'];
   }
   p->isword=1;
}
struct tnode*talloc()
{
    int i;
    struct tnode*p;
    p=(struct tnode*)malloc(sizeof(struct tnode));
    p->isword=0;p->isleaf=1;
    for(i=0;i<26;i++){
        p->ptr[i]=NULL;
    }
    return p;
}







