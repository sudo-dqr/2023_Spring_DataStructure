#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
char s[20480];
int n,op,top,back;
struct OPTION{
	int op,pos,n;
	char str[5200];
}pre[15],now[1024];
void Insert(struct OPTION a){
	int pos=a.pos,len=strlen(s);
	char tmp[5200];
	memset(tmp,0,sizeof(tmp));
	for(int i=pos;i<len;i++){
		tmp[i-pos]=s[i];
	}
	for(int i=0;i<strlen(a.str);i++)
	  s[i+pos]=a.str[i];
	s[pos+strlen(a.str)]=0;
	tmp[len]=0;
	strcat(s,tmp);
	return;
}
void DELETE_n(struct OPTION a){
	int pos=a.pos,len=strlen(s),cnt=a.n;
	if(cnt==0) return;
	if(cnt>len-pos){
		for(int i=pos;i<len;i++)
		  s[i]=0;
		return;
	}
	while(pos<len&&pos+cnt<len){
		s[pos]=s[pos+cnt];
		pos++;
	}
	for(int i=pos;i<len;i++){
		s[i]=0;
	}
	return;
}
int main()
{
//	freopen("s.in","r",stdin);
//	freopen("s.out","w",stdout);
	gets(s);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&pre[i].op,&pre[i].pos);
		scanf("%s",pre[i].str);
	}
	getchar();
	while(1){
		scanf("%d",&op);
		if(op==-1) break;
		if(op==1){
			now[++top].op=op;
			scanf("%d%s",&now[top].pos,now[top].str);
		}else if(op==2){
			now[++top].op=op;
			scanf("%d%d",&now[top].pos,&now[top].n);
		}else if(op==3){
			if(top>0) top--;
			else if(back<n) back++;
		}
	}
	for(int i=1;i<=back;i++){
		int tmp=n+1-i;
		if(pre[tmp].op==1){
			pre[tmp].n=strlen(pre[tmp].str);
			DELETE_n(pre[tmp]);
		}else{
			Insert(pre[tmp]);
		}
	}
	for(int i=1;i<=top;i++){
		if(now[i].op==1){
			Insert(now[i]);
		}else{
			DELETE_n(now[i]);
		}
	}
	puts(s);
	return 0;
}

