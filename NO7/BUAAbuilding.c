#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//最小生成树算法
int n,e;
typedef struct edge{
    int ID;//编号
    int adj;//终点
    int weight;//权重
    struct edge *link;
}Elink,*Elinkptr;
typedef struct vertex{
    Elinkptr link;
}Vlink,*Vlinkptr;
Vlink Vertex[100];
int path[100]={0},pos=0;//记录路径
int Weight[100]={0};//记录每条路权值
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
Elinkptr insertEDGE(Elinkptr head ,int weight,int adj,int id)
{
    Elinkptr p=(Elinkptr)malloc(sizeof(Elink));
    p->adj=adj;p->weight=weight;p->ID=id;p->link=NULL;
    if(head==NULL)head=p;
    else{
        Elinkptr q=head;
        for(;q->link!=NULL;q=q->link);
        q->link=p;
    }
    return head;
}
//用path存储已经选好的节点，pos记录个数
int A[100]={0},cnt1=0;//已经连线的顶点集合
int INA(int x)
{
    int j;
    for(j=0;j<cnt1;j++)
        if(A[j]==x)return 1;
    return 0;
}
Elinkptr FindMin(int ver)//找到权值最小的路径
{
    Elinkptr q=(Elinkptr)malloc(sizeof(Elink));
    q->weight=10000;
    Elinkptr p=Vertex[ver].link;
    if(p==NULL)return NULL;
    else{
        for(;p!=NULL;p=p->link)
            if(p->weight<q->weight&&(!INA(p->adj)))
                q = p;//q记录最小路径的边结点
    }
    return q;
}
void MinSpanTree_Prim(int ver)//无论从哪个顶点开始最小生成树是相同的
{
    A[cnt1++]=ver;//第一个顶点加入
    Elinkptr minptr=(Elinkptr)malloc(sizeof(Elink));
    minptr->weight=10000;minptr->ID=-1;minptr->adj=-1;minptr->link=NULL;
    while(cnt1<n){//n个结点都进入A时结束
        minptr->weight=10000;
       for(int i=0;i<cnt1;i++){
           Elinkptr q= FindMin(A[i]);
          if(minptr->weight>q->weight)
              minptr=q;
       }
       A[cnt1++]=minptr->adj;
       path[pos++]=minptr->ID;
    }
}
void GetSum()
{
    int sum=0;
    for(int i=0;i<pos;i++)
        sum=sum+Weight[path[i]];
    printf("%d\n",sum);
}
void print()
{
    for(int i=0;i<pos;i++)
        printf("%d ",path[i]);
}
int main()
{
    memset(Vertex,0,sizeof(Vertex));
    int id,ver,adj,weight;
    scanf("%d%d",&n,&e);
    for(int i=1;i<=e;i++){
        scanf("%d%d%d%d",&id,&ver,&adj,&weight);
        Vertex[ver].link= insertEDGE(Vertex[ver].link,weight,adj,id);
        Vertex[adj].link= insertEDGE(Vertex[adj].link,weight,ver,id);
        Weight[id]=weight;
    }
    MinSpanTree_Prim(0);
   // for(int i=0;i<pos;i++)printf("%d ",path[i]);
    qsort(path,pos,sizeof(path[0]),cmp);
    GetSum();
    print();
    return 0;
}

