#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
int a[510];//储存每次选出来的数据
int book[510];//记录是否被访问
int ans=0;//记录符合条件的次数
int check(参数)
{
    if(满足条件)
     return 1;
     return 0;
}
void dfs(int step)
{
	判断边界
	{
		相应操作 
	 } 
	尝试每一种可能
	{
		满足check条件
		标记
		继续下一步dfs(step+1)
		恢复初始状态(回溯的时候用到) 
	 } 
}

int a[510];   //存储每次选出来的数据
int book[510];   //标记是否被访问
int ans = 0; //记录符合条件的次数

void DFS(int cur){
	if(cur == k){ //k个数已经选完，可以进行输出等相关操作 
		for(int i = 0; i < cur; i++){
			printf("%d ", a[i]);
		} 
		ans++;
		return ;
	}
	
	for(int i = 0; i < n; i++){ //遍历 n个数，并从中选择k个数 
		if(!book[i]){ //若没有被访问 
			book[i] = 1; //标记已被访问 
			a[cur] = i;  //选定本数，并加入数组 
			DFS(cur + 1);  //递归，cur+1 
			book[i] = 0;  //释放，标记为没被访问，方便下次引用 
		}
	}
}

/*
深度优先算法  depth first search
简称DFS  属于盲目搜索 最糟糕时间复杂度为O(!n) 
一.基本思想
1.为了求得问题的解，先选择某一种可能情况向前探索
2.在探索过程中，一旦发现原来的选择是错误的
就退回一步重新选择，继续向前探索
3.如此反复进行，直至得到解或证明无解
 
二.操作步骤
在原始节点一直往下走，直到后面没有元素，
就回溯到距离最近的且链接有没访问结点的结点 

三.DFS模板
 
 
*/

