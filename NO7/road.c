#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct edge{//边结点
    int adj;//路径终点
    int pathID;//路径编号
    struct edge*link;
}Elink,*Elinkptr;
typedef struct vertex{//顶点结点
    struct edge*link;
}Vlink,*Vlinkptr;
struct vertex Vertex[100];
int Visited[200]={0};
int Path[20]={0};//路径
int n,e,pathBegin=0,pathEnd;
Elinkptr insertEDGE(Elinkptr head,int ID,int adj)
{
    //建立新边结点
    Elinkptr p=(Elinkptr)malloc(sizeof(Elink));
    p->pathID=ID;p->adj=adj;p->link=NULL;
   if(head==NULL){
       head=p;
   }
   else{
       Elinkptr q=head;
       for(;q->link!=NULL;q=q->link);
       q->link=p;
   }
   return head;
}
void DFS(int v,int depth)//递归+回溯算法
{
    Elinkptr p;
    if(v==pathEnd){
        for(int i=0;i<depth;i++)//输出路径
            printf("%d ",Path[i]);
        printf("\n");
        return ;
    }
    for(p=Vertex[v].link;p!=NULL;p=p->link){
        if(!Visited[p->adj]){
            Path[depth]=p->pathID;
            Visited[p->adj]=1;
            DFS(p->adj,depth+1);
            Visited[p->adj]=0;//回溯关键
        }
    }
}
int main()
{
    int ID,i,ver,adj;
    memset(Vertex,0,sizeof(Vertex));
    scanf("%d%d",&n,&e);
    for( i=0;i<e;i++){
        scanf("%d%d%d",&ID,&ver,&adj);
        Vertex[ver].link= insertEDGE(Vertex[ver].link,ID,adj);
        Vertex[adj].link= insertEDGE(Vertex[adj].link,ID,ver);
    }
    Visited[0]=1;
    pathBegin=0,pathEnd=n-1;
    DFS(0,0);
    return 0;
}
