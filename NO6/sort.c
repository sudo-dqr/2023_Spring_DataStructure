#include<stdio.h>
#include<stdlib.h>
int sum=0;
void selectSort(int k[],int n)
{
    int i,j,d;
    int temp;
    for(i=0;i<n-1;i++){
        d=i;
        for(j=i+1;j<n;j++) {//从后n-i+1中选取
            sum++;
            if (k[j] < k[d])
                d = j; //找到后面最小的元素
        }
        if(d!=i)//放在排好队的序列最后面
        {
            temp=k[d];
            k[d]=k[i];
            k[i]=temp;
        }
    }
}
void bubbleSort(int k[],int n)
{
    int i,j,flag=1,temp;
    for(i=n-1;i>0&&flag==1;i--){
        flag=0;//每趟排序前flag置为0
        for(j=0;j<i;j++)
        {
            sum++;
            if(k[j]>k[j+1])
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
void adjust(int k[],int i,int n)//重新生成大顶堆
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n)
    {
        if(j+1<n&&k[j]<k[j+1])
            j++;
        sum++;
        if(temp>=k[j]){
           break;
        }
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}
void heapSort(int k[],int n)
{
    int i,tmp=0;
    for(i=n/2-1;i>=0;i--)//i=n/2-1是最后一个分叉节点
        adjust(k,i,n);//建立初始堆
    for(i=n-1;i>=1;i--)//共n-1趟
    {
        tmp=k[i];//交换最大值到最后边
        k[i]=k[0];
        k[0]=tmp;
        adjust(k,0,i);//重新生成大顶堆
    }
}
void swap(int v[],int i,int j)
{
    int tmp;
    tmp=v[i];
    v[i]=v[j];
    v[j]=tmp;
}
void Qsort(int v[],int left,int right)
{
    int i,last;
    if(left>=right)return ;
    last=left;//last表示分界元素的位置
    for(i=left+1;i<=right;i++) {
        sum++;
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }
    swap(v,left,last);
    Qsort(v,left,last-1);//左半部分排序
    Qsort(v,last+1,right);//右半部分排序
}
void merge(int x[],int tmp[],int left,int leftend,int rightend)
{
    int i=left,j=leftend+1,q=left;
    while(i<=leftend&&j<=rightend) {
        sum++;
        if (x[i] <= x[j]) {
            tmp[q++] = x[i++];
        } else tmp[q++] = x[j++];
    }
    while(i<=leftend)tmp[q++]=x[i++];//复制剩余部分
    while(j<=rightend)tmp[q++]=x[j++];
    for(i=left;i<=rightend;i++) x[i]=tmp[i];
}
void mSort(int k[],int tmp[],int left,int right){
    int center,i;
    if(left<right){
        center=(left+right)/2;
        mSort(k,tmp,left,center);
        mSort(k,tmp,center+1,right);
        merge(k,tmp,left,center,right);
    }
}
void mergeSort(int k[],int n)
{
    int *tmp=(int *)malloc(sizeof(int)*n);
    if(tmp!=NULL){
        mSort(k,tmp,0,n-1);
        free(tmp);
    }
    else printf("no space for tmp array!\n");
}
int main()
{
    int op,i,n;
    int a[100]={0};
    scanf("%d%d",&n,&op);
    for(i=0;i<n;i++)scanf("%d",&a[i]);
    switch(op){
        case 1:selectSort(a,n);break;
        case 2:bubbleSort(a,n);break;
        case 3:heapSort(a,n);break;
        case 4:mergeSort(a,n);break;
        case 5:Qsort(a,0,n-1);
        default: break;
    }
    for(i=0;i<n;i++)printf("%d ",a[i]);
    printf("\n%d",sum);
}
/*需要注意的是，此题中的比较次数(sum)要写在判断语句if之外
 * 最初的错误是写在if之内 导致只有成功判断才能计数
 * */