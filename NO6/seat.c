#include<stdio.h>
#define min(m,n) ((m)<(n)?(m):(n))
struct student {
    int num;
    char name[50];
    int seat;
}Student[100];
void bubbleSort(struct student k[],int n)
{
    int i,j,flag=1;
    struct student temp;
    for(i=n-1;i>0&&flag==1;i--){
        flag=0;//每趟排序前flag置为0
        for(j=0;j<i;j++)
        {
            if(k[j].seat>k[j+1].seat)
            {
                temp=k[j];
                k[j]=k[j+1];
                k[j+1]=temp;
                flag=1;//有交换
            }else if(k[j].seat==k[j+1].seat){
                if(k[j].num>k[j+1].num)
                {
                    temp=k[j];
                    k[j]=k[j+1];
                    k[j+1]=temp;
                    flag=1;//有交换
                }
            }
        }
    }
}
int findmax(int n)
{
    int i=0,max=0;
    for(;i<n;i++){
        if(Student[i].seat>max)max=Student[i].seat;
    }
    return max;
}
void BubbleSort(struct student k[],int n)
{
    int i,j,flag=1;
    struct student temp;
    for(i=n-1;i>0&&flag==1;i--){
        flag=0;//每趟排序前flag置为0
        for(j=0;j<i;j++)
        {
            if(k[j].num>k[j+1].num)
            {
                temp=k[j];
                k[j]=k[j+1];
                k[j+1]=temp;
                flag=1;//有交换
                //如果没有交换就会退出排序
            }
        }
    }
}
void checkseat(int n)
{
    //注意是当前表中安排的最大座位号
    int m=findmax(n),top=n-1;
    int q=min(m,n);
    int seatflag[100]={0};//记录是否有人
    for(int i=0;i<n;i++){
        seatflag[Student[i].seat]++;
    }
    for(int i=1;i<=q;i++){
        if(seatflag[i]==0){
            seatflag[i]++;
            Student[top--].seat=i;
            q=min(findmax(n),n);
        }
    }
    m=findmax(n);
    bubbleSort(Student,n);
    for(int i=0;i<n;i++){
        int tmp=Student[i].seat,k=i;
        while(Student[i+1].seat==tmp)i++;
        int up=i;
        for(;up>k;up--){
            Student[up].seat=++m;
        }
    }
    BubbleSort(Student,n);
}
int main()
{
    char s[120]="0";
    int i=0,n;
    scanf("%d",&n);//n个学生
    FILE*src=fopen("in.txt","r");
    FILE*dst=fopen("out.txt","w");
    //首先按座位号从小到大进行排序
    while (1) {
        char *p = fgets(s, 120, src);
        if(p==NULL)break;
        else {
            sscanf(s, "%d %s %d", &Student[i].num, Student[i].name, &Student[i].seat);
            i++;//不要使用&student[i++]的形式 有bug
        }
    }
    bubbleSort(Student,n);
    checkseat(n);
    for(int j=0;j<n;j++){
        sprintf(s,"%d %s %d\n",Student[j].num,Student[j].name,Student[j].seat);
        fputs(s,dst);
    }
    fclose(src);
    fclose(dst);
    return 0;
}