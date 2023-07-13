#include<stdio.h>
#include<string.h>
#define M 618
#define INF 0x3f3f3f3f
struct station{
    char stationName[30];
    int IsChange;
};
struct vertex{
    int weight;
    int lineID;
};
struct station StationID_list[M];
struct vertex map[M][M];
int lineID,StationNum,lineNum,IsChange,VerNum;
int prev[M],dist[M],path[M],top;
char StationBegin[30],StationEnd[30];
int SearchMap(char *s)
{
    int i;
    for(i=0;i<VerNum;i++)
        if(strcmp(s,StationID_list[i].stationName)==0)
            return i;	//返回序号
    return -1;
}
void BuildMap(FILE *fp)
{
    int i,j,ContainID,EdgeLast;
    char stationName[30];
    fscanf(fp,"%d",&lineNum);
    for(i=0;i<lineNum;i++)
    {
        fscanf(fp,"%d %d",&lineID,&StationNum);
        EdgeLast=-1;	//每一条路线一开始都是 -1
        for(j=0;j<StationNum;j++)
        {
            fscanf(fp,"%s %d",stationName,&IsChange);
            ContainID=SearchMap(stationName);	//看看有没有
            if(ContainID == -1)		//没有
            {
                strcpy(StationID_list[VerNum].stationName,stationName);	//存储
                StationID_list[VerNum].IsChange=IsChange;				//存储
                if(EdgeLast != -1)		//如果有边的起点
                {
                    map[EdgeLast][VerNum].lineID=map[VerNum][EdgeLast].lineID=lineID;	//存储
                    map[EdgeLast][VerNum].weight=map[VerNum][EdgeLast].weight=1;		//存储
                }
                EdgeLast=VerNum;	//终点变起点
                VerNum++;			//总数 +1
            }
            else
            {
                if(EdgeLast != -1)	//如果有边的起点
                {
                    map[EdgeLast][ContainID].lineID=map[ContainID][EdgeLast].lineID=lineID;//存储
                    map[EdgeLast][ContainID].weight=map[ContainID][EdgeLast].weight=1;	//存储
                }
                EdgeLast = ContainID;	//终点变起点
            }
        }
    }
}
void dijkstra(int vs, int ve)
{
    int i,j,k,min,tmp;
    int flag[M];
    for (i = 0; i < VerNum; i++)
    {
        flag[i] = 0;
        prev[i] = vs;
        dist[i] = map[vs][i].weight;
    }
    dist[vs] = 0,flag[vs] = 1;
    for (i = 0; i < VerNum - 1; i++)
    {
        min = INF;
        for (j = 0; j < VerNum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;
        if(k==ve)	return;
        for (j = 0; j < VerNum; j++)
        {
            tmp = (map[k][j].weight==INF ? INF : (min + map[k][j].weight));
            if (flag[j] == 0 && (tmp  < dist[j]) && map[k][j].lineID>0)
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
}


void PrintPath(int v1,int v2)
{
    int i,EdgeLast=v1,pathLen=1,u=path[top-1];
    int lineId=map[EdgeLast][u].lineID;
    printf("%s-%d",StationID_list[v1].stationName,lineId);
    EdgeLast = u;
    for(i=top-2;i>=0;i--)
    {
        u=path[i];
        if(lineId != map[EdgeLast][u].lineID)
        {
            lineId = map[EdgeLast][u].lineID;
            printf("(%d)-%s-%d",pathLen,StationID_list[EdgeLast].stationName,lineId);
            pathLen=0;
        }
        pathLen++;
        EdgeLast = u;
    }
    printf("(%d)-%s",pathLen,StationID_list[v2].stationName);
}
void InitialMAP()
{
    int i,j;
    for(i=0;i<M;i++)
        for(j=0;j<M;j++)
        {
            map[i][j].weight=map[j][i].weight=INF;	//权重无穷大
            map[i][j].lineID=map[j][i].lineID=0;	//编号为0
        }
}
int main()
{
    FILE *fp = fopen("bgstations.txt","r");
    scanf("%s %s",StationBegin,StationEnd);
    InitialMAP();
     BuildMap(fp);
    int start=SearchMap(StationBegin);
    int end=SearchMap(StationEnd);
    dijkstra(start,end);
    int i;
    for(i=end;i!=start;i=prev[i])
    {
        path[top]=i;
        top++;
    }
    PrintPath(start,end);
    return 0;
}
