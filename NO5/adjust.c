#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct tnode{
    int num;
    struct tnode *child[3];
}Tnode,*Tnodeptr;
typedef struct node{
    int num;
    int people;
}Gate,*Gateptr;
int cmp(const void *a,const void *b)//二级排序
{
	if((*(struct node *)a).people!=(*(struct node *)b).people)
	return (*(struct node *)b).people>(*(struct node*)a).people? 1:-1;   
	else
	return(*(struct node*)a).num-(*(struct node *)b).num; 
 } 
Tnodeptr queue[1000],p;
int q[1000]={0};//存储层次遍历得到叶节点(登机口的序号)
void layerorder(Tnodeptr t)//进行中序遍历
{
    int front=-1,rear=0,top=0,i;
    if(t!=NULL)
    {
        queue[0]=t;
        while(front<rear)
        {
            p=queue[++front];
           if(p->child[0]==NULL&&p->child[1]==NULL&&p->child[2]==NULL)
              q[top++]=p->num;
              for(i=0;i<3;i++){
                if(p->child[i]!=NULL)
                queue[++rear]=p->child[i];
              }
        }
    }
}
Gate gate[100]={0};//对登机口排序
Tnode tnode[1000]={0};//模拟多叉树结构
int main()
{
    int id=0,number=0,i;
     scanf("%d",&id);//输入分叉点
    while(id!=-1){
        tnode[id].num=id;
        int ID=0,cnt=0;
         scanf("%d",&ID);//输入孩子节点，分岔口或登机口
        while(ID!=-1){
            if(ID<100)number++;
            tnode[ID].num=ID;
            tnode[id].child[cnt++]=&tnode[ID];
             scanf("%d",&ID);
        }
        scanf("%d",&id);
    }
    for(i=0;i<number;i++){
        scanf("%d%d",&gate[i].num,&gate[i].people);
    }
    qsort(gate,number,sizeof(gate[0]),cmp);
    Tnodeptr root=&tnode[100];//树根为num值为100分叉点
   layerorder(root);
    for(i=0;i<number;i++){
       printf("%d->%d\n",gate[i].num,q[i]);
    }
    return 0;
}