#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
//稳定排序与非稳定排序：对于值相同的两个元素，排序前后的先后次序不变,则称为稳定性排序方法，否则为非稳定排序方法
//稳定排序：插入排序，冒泡排序，归并排序，基数排序
//不稳定排序：选择排序，快速排序，希尔排序，堆排序

//约定这里的排序都是按关键字值从小到大排序！！！

//1.插入排序  n-1趟排序  数组下标从0开始  O(n^2)
/*思想：用k(i,j)表示第i趟排序结束后的第j个元素
第i趟排序将序列的第i+1个元素插入到一个大小为i，且已经按值有序排列的子序列
{k(i-1,1),k(i-1,2),...k(i-1,i)}中且保证仍然按值有序

算法分析：时间效率主要与元素之间的比较次数有关
事实上第一个元素是不需要进行排序的，需要进行插入的只有n-1个元素
1.若原始序列是一个按值递增的序列，则整个n-1趟排序只需要进行n-1次元素之间的比较(每一趟只与序列尾进行比较)
2.按值递减：第i趟排序比较i次 一共比较次数：n(n-1)/2
*/
void insertSort(int k[],int n)
{
    int i,j;
    int temp;
    for(i=1;i<n;i++)//共n-1趟排序
    {
        temp=k[i];
        for(j=i-1;j>=0&&temp<k[j];j--)//从后向前寻找插入位置
            k[j+1]=k[j];//没找到插入位置元素向后移
        k[j+1]=temp;//插入
    }
}
//插入排序的改进：采用折半查找确定插入位置
void insertSortPLUS(int k[],int n)
{
   int i,j,low,high,mid;
   int tmp;
   for(i=1;i<n;i++){
    tmp=k[i];
    low=0,high=i-1;//对前i个组成的序列进行折半查找
    while(low<=high){
        mid=(low+high)/2;
        if(tmp<k[mid])high=mid-1;
        else low=mid+1;
    }
    for(j=i-1;j>=low;j--)
    k[j+1]=k[j];
    k[low]=tmp;
   }
}
/*
上面的折半查找插入算法中low就是最终元素k[i]插入的位置
下面我分条分析：
1.小于序列中最小值 low=0;
2.大于序列中最大值 low>high=i-1,即 low=i;
3.在序列范围中，
注：如果出现元素相等情况 由于low=mid+1新元素会插入到后面
这就保持了相等元素前后顺序不变 是稳定性排序
*/



//2.选择排序  n-1趟  O(n^2)
/*
核心思想：第i趟排序从序列的后n-i+1个元素中选择一个值最小的元素
将其置于已经排好序的i个元素最后面
*/
void selectSort(int k[],int n)
{
    int i,j,d;
    int temp;
    for(i=0;i<n-1;i++){
        d=i;
        for(j=i+1;j<n;j++){//从后n-i+1中选取
            if(k[j]<k[d])d=j; //找到后面最小的元素
        }
        if(d!=i)//放在排好队的序列最后面
        {
            temp=k[d];
            k[d]=k[i];
            k[i]=temp;
        }
    }
}
/*
算法分析
无论初始序列是什么状态，第i趟排序都需要经过n-i次元素之间的比较
总比较次数为 n(n-1)/2
*/

/*
3.冒泡排序  总趟数范围:0-n-1
核心思想：第i趟排序对序列的前n-i+1个元素从第一个元素开始
依次做如下操作：相邻的两个元素比大小，若前者大于后者，两个元素交换位置
（最大值元素移动到最后）
*/
void bubbleSort(int k[],int n)
{
    int i,j,flag=1,temp;
    for(i=n-1;i>0&&flag==1;i--){
        flag=0;//每趟排序前flag置为0
        for(j=0;j<i;j++)
      {
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

/*
希尔排序 shell排序
首先确定一个元素的间隔数gap，将参加排序的元素按照gap分割成若干个子序列(分别把那些位置相隔gap的元素看作一个子序列)
然后对各个子序列采用某一种排序方法进行排序，此后减小gap值重复上述过程直到gap<1
*/
void shellSort(int k[],int n)
{
    int i,j,flag,gap=n;
    int temp;
    while(gap>1){
        gap=gap/2;
        do{
          flag=0;
          for(i=0;i<n-gap;i++){
            j=i+gap;
            if(k[i]>k[j]){//对每个子序列内部采用冒泡排序
                temp=k[i];
                k[i]=k[j];
                k[j]=temp;
                flag=1;
            }
          }
        }while(flag==1);
    }
}
void shellSORT(int k[],int n)
{
    int i,j,gap=n;
    int temp;
    while(gap>1){
        gap=gap/2;
        for(i=gap;i<n;i++){//内部插入排序
            temp=k[i];
            for(j=i;j>=gap&&k[j-gap]>temp;j-=gap)
            k[j]=k[j-gap];
            k[j]=temp;
        }
    }
}
//堆排序
/*
大顶堆与小顶堆
大顶堆：k(i)>=k(2i),k(i)>=k(2i+1);
小顶堆  k(i)<=k(2i),k(i)<=k(2i+1);
可以写成完全二叉树的形式 每一个分支结点的值都大于等于孩子结点的值

由数字序列建立大顶堆的方法：先建立出完全二叉树，再从最下面的分支节点开始观察三个人的关系
找到最大的调整到根节点，一层一层向上调整即可（也包括向下调整）

堆排序：第i趟排序将序列的前n-i+1个元素组成的子序列转换为一个堆积，然后将堆的第一个元素与堆的
最后那个元素交换位置
1.将原始序列转换为第一个堆
2.将堆的第一个元素与堆积的最后那个元素交换位置(去掉最大值元素)
3.将去掉最大安置元素后剩下的元素组成的子序列重新转换为一个堆
4.重复上述步骤n-1次
我们使用堆排序的实质是：利用大顶堆的特性，位于大顶堆根节点处的一定是现在待排序列中最大的元素，不断找到最大的元素放到序列末尾
*/
void adjust(int k[],int i,int n)//重新生成大顶堆
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n)
    {
        if(j+1<n&&k[j]<k[j+1])
        j++;
        if(temp<k[j]){
            k[(j-1)/2]=k[j];
            j=2*j+1;
        }
        else break;
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
/*快速排序
 * 从当前参加排序的元素中任选一个元素(通常称之为分界元素，第一个，最后一个后位置居中)，从当前参加排序的的元素中查找
 * 凡是大于分界元素的都移动到分界元素前面，大于分界元素的移动到分界元素的后面，分界元素将当前参加排序的元素分成前后两部分
   每一趟排序即可确定分界元素的最终位置，故进行到第i趟排序时至少有i个元素已经排好了位置，不断在分界元素左右进行排序直至需要排序部分长度小于1
 */
/*设置两个哨兵位 初始状态下i=0,j=n-1
 * i不断向右移动直到发现大于分界元素的记录，j不断向左移动直到发现小于的记录
 *i<j k[i]与k[j]交换位置(继续向下寻找)
 * i>=j key与k[j]交换位置(一趟排序结束)
 * */
//本例中寻找中间元素作为分界元素
//主程序中调用:Qsort(k,0,n-1);
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
    swap(v,left,(left+right)/2);//把中间元素移动得到最左边
    last=left;//last表示分界元素的位置
    for(i=left+1;i<=right;i++)
        if(v[i]<v[left])
            swap(v,++last,i);
        swap(v,left,last);
        Qsort(v,left,last);//左半部分排序
        Qsort(v,last+1,right);//右半部分排序
}
/*二路归并排序
 * 将两个位置相邻，并且各自按值有序的子序列合并为一个按值有序的子序列的过程称为二路归并
 * 思想：第i趟排序将序列的[n/(2^(i-1))]个长度为2^(i-1)的按值有序的子序列依次两两
 * 合并为n/(2^i)个长度为2^i的按值有序的子序列
 * */
//合并存储位置相邻且按值有序子序列算法
/*两个子序列的顺序存储可如下图表示
 * 0--leftend  ~  leftend+1--rightend
 * */
void merge(int x[],int tmp[],int left,int leftend,int rightend)
{
    int i=left,j=leftend+1,q=left;
    while(i<=leftend&&j<=rightend)
        if(x[i]<=x[j])
            tmp[q++]=x[i++];
        else tmp[q++]=x[j++];
    while(i<=leftend)tmp[q++]=x[i++];//复制剩余部分
    while(j<=rightend)tmp[q++]=x[j++];
    for(i=left;i<=rightend;i++) x[i]=tmp[i];
}
void mSort(int k[],int tmp[],int left,int right){
    int center;
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
    int a[]={1,6,2,3};
    Qsort(a,0,3);
    for(int i=0;i<4;i++)printf("%d ",a[i]);
    return 0;
}
