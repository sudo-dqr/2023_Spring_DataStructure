#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int f[101],sum;
int pos[101],len[101],maxl;
int tmp,n,minn,min_pos,history=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&pos[i],&len[i]);
		if(len[i]>maxl) maxl=len[i];
	}
	while(1){
		scanf("%d",&tmp);
		minn=maxl;min_pos=n+1;
		if(tmp==-1) break;
		for(int i=1;i<=n;i++){
			if(f[history]||len[history]<tmp){
				history++;
				if(history>n) history=1;
				continue;
			}
			if(tmp==len[history]){
				min_pos=history;
				break;
			}else if(minn>len[history]-tmp){
				minn=len[history]-tmp;
				min_pos=history;
			}
			history++;
			if(history>n) history=1;
		}
		if(min_pos!=n+1){
			if(len[min_pos]==tmp){
				f[min_pos]=1;
				sum++;
			}else len[min_pos]-=tmp;
			history=min_pos;
		}else continue;
	}
	while(sum<n){
		while(f[history]){
			history++;
			if(history>n) history=1;
			continue;
		}
		printf("%d %d\n",pos[history],len[history]);
		f[history]=1;
		sum++;
	}
	return 0;
}

