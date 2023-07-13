//本题是遍历图的基本题，使用邻接矩阵即可解决，(使用邻接表失败)
//并且使用邻接矩阵按照顺序访问即可实现对于邻接结点按照数字从小到大访问，对于邻接表的初步设想为需要在每一条链表中插入排序
//附加：邻接矩阵删除节点del 即visited[del]=1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000
int n,e;
int visited[MAX]={0};
int matrix[MAX][MAX];//实际是n*n矩阵
void travelDFS(int ver)//前序遍历
{
  printf("%d ",ver);
  visited[ver]=1;//输出即置1
  for(int i=0;i<n;i++){
      if(matrix[ver][i]&&!visited[i])
          travelDFS(i);
  }
}
void travelBFS(int ver)//层序遍历
{
   int queue[MAX]={0};
   int front=0,rear=0;
   queue[rear++]=ver;
   while(front<=rear){
       int tmp=queue[front++];//出队
       if(!visited[tmp])
       {
           printf("%d ",tmp);
           visited[tmp]=1;
           for(int i=0;i<n;i++){
               if(matrix[tmp][i]&&!visited[i]){
                   queue[rear++]=i;
               }
           }
       }
   }

}
int main()
{
    memset(matrix,0,sizeof(matrix));
    int i,ver,adj,del;
    scanf("%d%d",&n,&e);
    for(i=1;i<=e;i++){
        scanf("%d%d",&ver,&adj);
        matrix[ver][adj]=1;//无向图赋值对称矩阵
        matrix[adj][ver]=1;
    }
    scanf("%d",&del);
    memset(visited,0,sizeof(visited));
    travelDFS(0);printf("\n");
    memset(visited,0,sizeof(visited));//注意每次重新遍历visited置空
    travelBFS(0);printf("\n");
    memset(visited,0,sizeof(visited));
    visited[del]=1;
    travelDFS(0);printf("\n");
    memset(visited,0,sizeof(visited));//注意每次重新遍历visited置空
    visited[del]=1;
    travelBFS(0);
}
