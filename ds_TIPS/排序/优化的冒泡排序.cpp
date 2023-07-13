//优化的冒泡排序   注意1.再用排序的时候一定要是全局数组
                    //2.数组输入时下标一定要从0开始
#include<stdio.h>
void optiBubbleSort(int a[],int n);

void optiBubbleSort(int a[],int n){
 int  swap_flag=0;
	int temp=0;
	for(int i=1;i<=(n-1);i++){
		for(int j=0;j<(n-i);j++){
			if(a[j]>a[j+1]){
				swap_flag=1;
			    temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
		if(swap_flag==0){
			break;
		}	
	}	
}
