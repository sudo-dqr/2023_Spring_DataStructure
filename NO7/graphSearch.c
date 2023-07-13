#include<stdio.h>
#include<string.h>
int matrix[100][100],visited[100]={0},Queue[100]={0},n;
void DFS(int ver)
{
    int i;
    printf("%d ",ver);
    visited[ver]=1;
    for(i=0;i<n;i++) {
       if(matrix[ver][i]&&!visited[i])//邻接矩阵的行遍历自然为从小到大
           DFS(i);
    }
}
void BFS(int ver)
{
   int front=0,rear=0;
   Queue[rear++]=ver;
   while(front<=rear){
       int tmp=Queue[front++];
       if(!visited[tmp]){
           printf("%d ",tmp);
           visited[tmp]=1;
           for(int i=0;i<n;i++){
               if(matrix[tmp][i]&&!visited[i])
                   Queue[rear++]=i;
           }
       }

   }
}
int main()
{
    memset(matrix,0,sizeof(matrix));
    int e,i,ver,adj,delete;
    scanf("%d%d",&n,&e);
    for(i=0;i<e;i++){
        scanf("%d%d",&ver,&adj);
        matrix[ver][adj]=1;matrix[adj][ver]=1;
    }
    scanf("%d",&delete);
    memset(visited,0,sizeof(visited));
    DFS(0);printf("\n");
    memset(visited,0,sizeof (visited));
    BFS(0);printf("\n");
    memset(visited,0,sizeof(visited));
    visited[delete]=1;//从图中删除某个顶点 visited置为1
    DFS(0);printf("\n");
    memset(visited,0,sizeof(visited));
    visited[delete]=1;
    BFS(0);
    return 0;
}