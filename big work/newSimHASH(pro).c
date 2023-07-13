#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXPAGE 20000
#define MAXSIZE 1e7  //可以用宏定义解决参数类型不匹配问题1e7是double类型
#define MAXSTOP 10000
#define MAXWORD  6000000
typedef struct stopword{
    char stopword[100];
    struct stopword*link;
}Stopword,*Stopwordptr;
Stopwordptr STOPWORD[MAXSTOP]={NULL};
typedef struct wordlist{
    char word[100];
    int weight;
    struct wordlist*link;
}Wordlist,*Wordlistptr;
Wordlistptr WORDLIST[MAXWORD]={NULL};
struct web{
    char webID[20];
    char fingerprint[200];
};
struct web article[MAXPAGE];
struct web sample[MAXPAGE];
unsigned int SDBMHash(char *str,unsigned int size)
{
    unsigned int hash=0;
    while(*str){
        hash=(*str++)+(hash<<6)+(hash<<16)-hash;
    }
    return (hash%size);//将产生的hash值锁定在0-size之间，size越大理论上发生的冲突越少
}
int N,M;
char buffer[10000000];
void StopwordHASH()
{
    FILE* src=fopen("stopwords.txt","r");
    char word[100];
    memset(word,0,sizeof(word));
    memset(buffer,0,sizeof(char)*MAXSIZE);
    fread(buffer,sizeof(char ),MAXSIZE-1,src);
    int i;
    for( i=0;buffer[i];i++){
        int j=0;
        if(!isalpha(buffer[i]))continue;
        while(isalpha(buffer[i])){
            word[j++]= tolower(buffer[i++]);
        }word[j]='\0';
        unsigned  int hash= SDBMHash(word,MAXSTOP);
        Stopwordptr p=(Stopwordptr)malloc(sizeof(Stopword));
        strcpy(p->stopword,word);p->link=NULL;
        if(STOPWORD[hash]==NULL) STOPWORD[hash]=p;//未发生冲突
        else{
            Stopwordptr tmp=STOPWORD[hash];
            while(tmp->link!=NULL)
                tmp=tmp->link;
            tmp->link=p;
        }
    }
    fclose(src);
}
int Search(char *word)
{
    unsigned int tmp= SDBMHash(word,1e6);
    if(WORDLIST[tmp]==NULL)return 0;
    else {
        Wordlistptr p=WORDLIST[tmp];
        while(p!=NULL){
            if(strcmp(word,p->word)==0){//对已有单词查重
                p->weight++;//找到就频次加1
                return 1;
            }
            p=p->link;
        }
        return 0;
    }
}
int isStopWord(char *w)
{
    unsigned int tmp= SDBMHash(w,MAXSTOP);
    if(STOPWORD[tmp]==NULL)return 0;
    else{
        Stopwordptr p=STOPWORD[tmp];
        for(;p!=NULL;p=p->link)
            if(strcmp(p->stopword,w)==0)return 1;
    }
    return 0;
}
Wordlistptr ptr[MAXWORD]={NULL};
int ptrcnt=0;
int getword(FILE* fp,char *w)
{
    int c;
    while(!isalpha(c=fgetc(fp)))
        if(c==EOF)return 0;
        else continue;
    do
    {
        *w++=tolower(c);
    }while(isalpha(c=fgetc(fp)));
    *w='\0';
    return 1;
}
void Staticword()
{
    char word[100];
    FILE *src=fopen("article.txt","r");
    while(getword(src,word)){
        if((!Search(word))&&(!isStopWord(word))) {
            unsigned int hash = SDBMHash(word, 1e6);
            //额外建立指针数组存储hash表中每一个单词结点，再对此指针数组进行快排
            Wordlistptr p = (Wordlistptr) malloc(sizeof(Wordlist));
            strcpy(p->word, word);
            p->weight = 1;p->link = NULL;
            ptr[ptrcnt++] = p;//用指针数组存储每一个单词结点的地址
            if (WORDLIST[hash] == NULL)WORDLIST[hash] = p;
            else {
                Wordlistptr q = WORDLIST[hash];
                while (q->link != NULL)q = q->link;
                q->link = p;
            }
        }
    }
    fclose(src);
}
int cmp(const void *a,const void *b)
{
    Wordlistptr *aa=(Wordlistptr*)a;
    Wordlistptr *bb=(Wordlistptr*)b;
    if((*aa)->weight>(*bb)->weight){
        return -1;
    }else if((*aa)->weight==(*bb)->weight){
        return strcmp((*aa)->word,(*bb)->word);
    }else{
        return 1;
    }
}
Wordlistptr VectorHASH[1000000]={NULL};//关键词hash表(N个)
Wordlistptr ptr2[MAXWORD]={NULL};
int ptr2cnt=0;
void VectorWordHASH()//关键单词HASH表
{
    for(int i=0;i<N;i++){//利用指针数组建立hash表
        unsigned int hash= SDBMHash(ptr[i]->word,1000000);
        Wordlistptr p=(Wordlistptr)malloc(sizeof(Wordlist));
        strcpy(p->word,ptr[i]->word);
        p->link=NULL;p->weight=0;
        ptr2[ptr2cnt++]=p;//记录关键词地址
        if(VectorHASH[hash]==NULL)VectorHASH[hash]=p;
        else{
            Wordlistptr q=VectorHASH[hash];
            while(q->link!=NULL)q=q->link;
            q->link=p;
        }
    }
}
int isVector(char *w)//是不是关键单词
{
    unsigned int hash= SDBMHash(w,1000000);
    if(VectorHASH[hash]==NULL)return 0;
    else {
        Wordlistptr p=VectorHASH[hash];
        for(;p!=NULL;p=p->link){
            if(strcmp(p->word,w)==0){
                p->weight++;
                return 1;
            }
        }
        return 0;
    }
}
int weight1[MAXPAGE][10000];
int weight2[MAXPAGE][10000];
int page1=0,page2=0;
int GetWord(FILE*fp,char *word,struct web* a,int *pagen,int weightn[MAXPAGE][10000])
{
    int ch;
    while(!isalpha(ch=fgetc(fp))) {
        if (ch == EOF){
            if(pagen==&page1){
                for (int i = 0; i < N; i++) {
                    weightn[*pagen][i] = ptr2[i]->weight;
                    ptr2[i]->weight = 0;
                }
                (*pagen)++;
                return 0;
            }else{
                return 0;
            }
        }
        else if (ch == '\f') {
            for (int i = 0; i < N; i++) {
                weightn[*pagen][i] = ptr2[i]->weight;
                ptr2[i]->weight = 0;
            }
            (*pagen)++;
            fscanf(fp, "%s", (a + *pagen)->webID);
            //换页时就应该对上一页的词频进行统计，生成权重行
        } else continue;
    }
    do{
        *word++=tolower(ch);
    }while(isalpha(ch=fgetc(fp)));
    *word='\0';
    return 1;
}
void GetEachWeb(FILE *fp,struct web*a,int *pagen,int weightn[MAXPAGE][10000])//对每个网页统计
{
    char word[100];
    memset(word,0,sizeof(word));
    fscanf(fp,"%s",(a+*pagen)->webID);//读入第一行网页ID
    while(GetWord(fp,word,a,pagen,weightn)){
        if(isVector(word)){
            continue;
        }
    }
}
char HASHstr[10001][129];//存储hash串
void GetHASH()//提取hash串
{
    FILE *src=fopen("hashvalue.txt","r");
    for(int i=0;i<N;i++){
        fscanf(src,"%s",HASHstr[i]);
        HASHstr[i][M]='\0';
    }
    if(src!=NULL) fclose(src);
}
//计算hamming距离
int HammingDistance(char *s1,char *s2)
{
    int dis=0;
    for(int i=0;i<strlen(s1);i++){
        if(s1[i]!=s2[i])dis++;
    }
    return dis;
}
void FINGERPRINT(int pagen,struct web*a,int weightn[MAXPAGE][10000])
{
    for(int i=0;i<=pagen;i++) {
        if (strlen((a + i)->webID) == 0)continue;//特判sample中的第10行
        else {
            int matrix[N][M];
            int finger[1000] = {0};//指纹有 M位，单词有N个，频次有N个
            memset(matrix, 0, sizeof(matrix));
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < M; j++) {
                    if (HASHstr[k][j] == '1')
                        matrix[k][j] = weightn[i][k];
                    else matrix[k][j] = -weightn[i][k];
                }
            }
            for (int l = 0; l < M; l++) {
                for (int p = 0; p < N; p++) {
                    finger[l] = finger[l] + matrix[p][l];
                }
            }
            for (int o = 0; o < M; o++) {
                if (finger[o] > 0)(a + i)->fingerprint[o] = '1';
                else (a + i)->fingerprint[o] = '0';
            }
            (a + i)->fingerprint[M] = '\0';
        }
    }
}

struct web PTR[4][10000];
int pos0,pos1,pos2,pos3;
void FINGERPRINT2(int pagen,struct web*a,int weightn[MAXPAGE][10000])
{
    FILE *dst=fopen("result.txt","w");
    for(int i=0;i<pagen;i++) {
        memset(PTR,0,sizeof(PTR));
        pos0=0,pos1=0,pos2=0,pos3=0;
            int matrix[N][M];
            int finger[1000] = {0};//指纹有 M位，单词有N个，频次有N个
            memset(matrix, 0, sizeof(matrix));
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < M; j++) {
                    if (HASHstr[k][j] == '1')
                        matrix[k][j] = weightn[i][k];
                    else matrix[k][j] = -weightn[i][k];
                }
            }
            for (int l = 0; l < M; l++) {
                for (int p = 0; p < N; p++) {
                    finger[l] = finger[l] + matrix[p][l];
                }
            }
            for (int o = 0; o < M; o++) {
                if (finger[o] > 0)(a + i)->fingerprint[o] = '1';
                else (a + i)->fingerprint[o] = '0';
            }
            (a + i)->fingerprint[M] = '\0';
        fprintf(dst,"%s\n",sample[i].webID);
        for(int m=0;m<page1;m++){
            if(HammingDistance(sample[i].fingerprint,article[m].fingerprint)==0)PTR[0][pos0++]=article[m];
            else if(HammingDistance(sample[i].fingerprint,article[m].fingerprint)==1)PTR[1][pos1++]=article[m];
            else if(HammingDistance(sample[i].fingerprint,article[m].fingerprint)==2)PTR[2][pos2++]=article[m];
            else if(HammingDistance(sample[i].fingerprint,article[m].fingerprint)==3)PTR[3][pos3++]=article[m];
            else continue;
        }
        if(pos0>0){
            fprintf(dst,"%s","0:");
            for(int x=0;x<pos0;x++)fprintf(dst,"%s ",PTR[0][x].webID);
            fputc('\n',dst);
        }
        if(pos1>0){
            fprintf(dst,"%s","1:");
            for(int x=0;x<pos1;x++)fprintf(dst,"%s ",PTR[1][x].webID);
            fputc('\n',dst);
        }
        if(pos2>0){
            fprintf(dst,"%s","2:");
            for(int x=0;x<pos2;x++)fprintf(dst,"%s ",PTR[2][x].webID);
            fputc('\n',dst);
        }
        if(pos3>0){
            fprintf(dst,"%s","3:");
            for(int x=0;x<pos3;x++)fprintf(dst,"%s ",PTR[3][x].webID);
            fputc('\n',dst);
        }
    }
    fclose(dst);
}

int main(int argc,char *argv[]) {
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    StopwordHASH();
    Staticword();
    qsort(ptr, ptrcnt, sizeof(ptr[0]), cmp);
    VectorWordHASH();
    FILE*src=fopen("article.txt","r");
    GetEachWeb(src,article,&page1,weight1);
    fclose(src);
    FILE*src2=fopen("sample.txt","r");
    GetEachWeb(src2,sample,&page2,weight2);
    fclose(src2);
    GetHASH();
    FINGERPRINT(page1,article,weight1);
    FINGERPRINT2(page2,sample,weight2);
    return 0;
}




