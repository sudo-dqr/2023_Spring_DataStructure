#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NHASH 3001
#define MULT 37
char dic[3500][20];
int row=0;
int excel[200]={0};
unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str;*p!='\0';p++){
        h=MULT*h+*p;
    }
    return h%NHASH;
}
int find(char str[],int *cnt)//顺序查找
{
    for(int i=0;i<row;i++){
        (*cnt)++;
        if(strcmp(str,dic[i])==0){
            return 1;
        }else if(strcmp(str,dic[i])<0){
            break;
        }
    }
    return 0;
}
int Binaryfind(char str[],int *cnt)
{
   int low=0,high=row-1;
   while(low<=high){
       (*cnt)++;
       int mid=(low+high)/2;
       if(strcmp(dic[mid],str)<0)low=mid+1;
       else if(strcmp(dic[mid],str)>0)high=mid-1;
       else return 1;
   }
   return 0;
}
void Excel(){
    FILE *src=fopen("dictionary3000.txt","r");
    char word[30]="0";
    while(1){
        char *p=fgets(word,30,src);
        if(p==NULL)break;
        else{
            excel[word[0]]++;
        }
    }
    fclose(src);
}

int IndexSequalSearch(char str[],int *cnt)
{
     int i=str[0]-'a',j,low=0,high,mid;
     for(j=0;j<i;j++){
         low=low+excel['a'+j];
     }
     high=low+excel[str[0]]-1;
     while(low<=high){
         (*cnt)++;
          mid=(low+high)/2;
         if(strcmp(str,dic[mid])<0)high=mid-1;
         else if(strcmp(str,dic[mid])>0)low=mid+1;
         else return 1;
     }
     return 0;
}
struct hash{
    char str[30];
    struct hash*link;
};
struct hash* HASH[100000];
int hashSearch(char str[],int *cnt)
{
    memset(HASH,0,sizeof(HASH));
    for(int i=0;i<row;i++){
            unsigned int a=hash(dic[i]);
            struct hash* q=(struct hash*)malloc(sizeof(struct hash));
            strcpy(q->str,dic[i]);
            q->link=NULL;
            if(HASH[a]==NULL){
                HASH[a]=q;
            }else{
                struct hash *m=HASH[a],*prem=m;
                //按字典序排列
                while(m!=NULL&&strcmp(q->str,m->str)>0){
                    prem=m;
                    m=m->link;
                }
                if(m==NULL){
                    prem->link=q;
                }
                else{
                    prem->link=q;
                    q->link=m;
                }
            }
    }
    unsigned int b=hash(str);
    if(HASH[b]==NULL)return 0;
    else{
        struct hash*q=HASH[b];
        for(;q!=NULL;q=q->link){
            (*cnt)++;
            if(strcmp(q->str,str)==0) return 1;
            else if(strcmp(q->str,str)>0) return 0;
        }
    }
    return 0;
}
int main()
{
    FILE *src=fopen("dictionary3000.txt","r");
    char s[40];
    while(1){
        char *p=fgets(s,30,src);
        if(p==NULL)break;
        else  {
            char *q=strstr(s,"\r");
            if(q!=NULL)*q='\0';
            q=strstr(s,"\n");
            if(q!=NULL)*q='\0';
            strcpy(dic[row++],s);
        }
    }
    fclose(src);
    Excel();
    char str[40];
    int op=0,cnt=0,ok=0;
    scanf("%s %d",str,&op);
        if(op==1)
            ok=find(str,&cnt);
        else if(op==2)
            ok=Binaryfind(str,&cnt);
        else if(op==3)
            ok=IndexSequalSearch(str,&cnt);
        else
        {
            ok=hashSearch(str,&cnt);
        }
   printf("%d %d",ok,cnt);
    return 0;
}
