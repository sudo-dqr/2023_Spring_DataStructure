/*基本概念梳理
 * 1.simhash算法：google提出解决网页去重任务，simhash常用于解决长文本，将长文本压缩至
 *几个关键词来代表一篇文章，再将关键词编码成固定长度的二进制字符串（32/64）
 *这样用一个固定长度的编码来表示一篇文章，对比多篇文章，只需要对比这些固定长度的编码
 *2.停用词：文本分析时不提供额外语义信息的词的列表，如a an he you 具体见停用词表 stopwords.txt
 *3.汉明距离：两个相同长度字符串对应位置的不同字符的数量，对两个字符串进行异或运算，统计结果为1的数量即为汉明距离

  检测方法实现：
 * 0.输入：从命令行输入特征向量长度N以及指纹长度M
 * 1.获取网页特征向量，统计非停用词词频（从高到低），频度相同按字典序，取前N个单词构成网页特征向量
 *   注意：统计时将大写英文字母转换为小写英文字母  网页特征向量feature = (word1,word2,...wordn)
 * 2.统计每个网页的特征向量中每个特征（单词）的频度，得到对应的权重向量 weight=(w1,w2...wn)
 * 3.每个特征单词wordi都有一个对应哈希值串 hashi,网页特征向量对应权重向量中wi按照hashi进行符号取值
 * 得到由wi与-wi组成的符号化权重值向量SignWeighti(hashi串中1代表1，0代表-1)
 * 4.计算网页指纹fingerprint 特征向量的所有特征对应的符号化权重向量对应位置值累加，对累加结果大于0置1，小于等于0置0
 * 即sign={1|0,x>0 sign=1;x<=0,sign=0}
 *   案例计算过程：
 *   word1(w1)->hash1->100110(w1)->w1 -w1 -w1  w1  w1 -w1
 *   word2(w2)->hash2->110000(w2)->w2  w2 -w2 -w2 -w2 -w2
 *   ...                                 对应分量相加
 *   wordn(wn)->hashn->001001(wn)->-wn -wn wn -wn -wn  wn
 *                                  a1 a2  a3  a4  a5  a6
 *                                  最后根据ai正负性生成fingerprint
 *                                  sign={1|0,x>0 sign=1;x<=0,sign=0}
 * 5.按上面方法计算新抓取网页的指纹
 * 6.指纹相似度通过汉明距离进行计算，超过某个阈值判断为不相似，小于等于阈值判断为相似
 * 7.输出 依次将新抓取网页与已有相似网页（汉明距离在3以内）按照汉明距离从小到大输出到屏幕和指定文件
 *
 * 对于各个文件的解释：
 * 1.stopwords.txt停用词表 已经按字典序排序
 * 2.hashvalue.txt 10000*128 当输入特征向量N=1000 指纹长度M=16时，取文件中前1000行，每行前16列作为实际哈希表使用
 * 3.article.txt已有网页数据文件
 * 4.sample.txt待查重网页数据文件
 * */
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char stopwords[330][50];
int cnt=0,N,M,n=0;
struct VectorWord{
    char word[100];
    int weight;
}VecTor[106000];
int Excel[200]={0};
struct tnode{
  char isleaf;
  int weight;
  char isword;
  int visited;
  struct tnode*ptr[26];
};
int cmp(const void *a,const void *b)
{
    if((*(struct VectorWord *)a).weight!=(*(struct VectorWord *)b).weight)
        return (*(struct VectorWord *)a).weight<(*(struct VectorWord*)b).weight? 1:-1;
    else
        return(strcmp((*(struct VectorWord *)a).word,(*(struct VectorWord *)b).word));
}
int SearchTree(struct tnode*root,char *w)
{
    if(root==NULL)return 0;
    else{
        struct tnode*p=root;
        for(;*w!='\0';w++){
            if(p->ptr[*w-'a']==NULL){
               return 0;
            }else
                p=p->ptr[*w-'a'];
        }
      for(int i=0;i<26;i++){
          if(p->ptr[i]!=NULL){
              return 0;
          }
      }
      p->weight++;
      return 1;
    }
}
struct tnode *talloc()
{
    int i;
    struct tnode*p=(struct tnode*)malloc(sizeof(struct tnode));
    p->isword=0;p->weight=0;p->isleaf=1;p->visited=0;
    for(i=0;i<26;i++)p->ptr[i]=NULL;
    return p;
}
void wordTree(struct tnode*root,char *w)
{
    struct tnode*p=root;
    for(;*w!='\0';w++){
        if(p->ptr[*w-'a']==NULL){
            p->ptr[*w-'a']=talloc();
            p->isleaf=0;
        }
        p=p->ptr[*w-'a'];
    }
    p->isword=1;p->weight=1;
}
//hash算法
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}
void GetStopWords()
{
    memset(Excel,0,sizeof(Excel));
    memset(stopwords,0,sizeof(stopwords));
    char *buffer=(char *)malloc(sizeof(char)*4e7);
    FILE *fp= fopen("stopwords.txt","rb");
    fread(buffer,sizeof(char),4e7,fp);
    int pos=0,i;
    for( i=0;i<strlen(buffer);i++){
        if(buffer[i]=='\r'||buffer[i]=='\n')pos=0;
        else{
            while(isalpha(buffer[i])){
                stopwords[cnt][pos++]=buffer[i++];
            }
            Excel[stopwords[cnt][0]]++;
           cnt++;
        }
    }
    fclose(fp);
}
//查找是不是停用词考虑使用索引查找，思路与第六次作业相近
int isStopwords(char s[])
{
    int dis=s[0]-'a',low=0,high,i;
    for( i=0;i<dis;i++) {
        low += Excel['a' + i];
    }
    high=low+Excel[s[0]]-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(strcmp(s,stopwords[mid])<0)high=mid-1;
        else if(strcmp(s,stopwords[mid])>0)low=mid+1;
        else return 1;
    }
    return 0;
}
char word[100]="";
int j=0;
struct tnode*root0;
void TraverseTree(struct tnode*p)
{
    struct tnode*q=p;
    //q->visited=1;
    for(int i=0;i<26;i++){
        if(q->ptr[i]!=NULL){
            //q->ptr[i]->visited=1;
            word[j++]=i+'a';
            if(q->ptr[i]->weight>0){//是单词结点,查看是否还有同前缀单词
                int son=0,flag=0;word[j]='\0';
                strcpy(VecTor[n].word,word);
                VecTor[n++].weight=q->ptr[i]->weight;
                for(;son<26;son++){
                    if(q->ptr[i]->ptr[son]!=NULL){
                        flag=1;
                       // q->ptr[i]->ptr[son]->visited=1;
                        word[j++]=son+'a';
                        TraverseTree(q->ptr[i]->ptr[son]);
                    }
                }
                if(flag==0){
                    //无继续的单词
                    q->ptr[i]->visited=1;
                    j=0;
                    memset(word,0,sizeof(word));
                    q->ptr[i]->visited=0;
                    TraverseTree(root0);
                }
            }
            else{
                TraverseTree(q->ptr[i]);
            }
        }
    }
}
void BuildTree(struct tnode *root)//对所有网页中词频进行统计
{
   char *buffer=(char *)malloc(sizeof(char)*4e7);
   FILE*fp=fopen("article2.txt","rb");
   fread(buffer,sizeof(char),4e7,fp);
   char tmpword[120];
    int pos=0;
    for(int i=0;i<strlen(buffer);i++) {
        memset(tmpword,0,sizeof (tmpword));
        if (isalpha(buffer[i])) {
            while (isalpha(buffer[i])) {
                tmpword[pos++] = tolower(buffer[i++]);
            }
            tmpword[pos] = '\0';pos = 0;
            if((!isStopwords(tmpword))&&(!SearchTree(root,tmpword))) {
                wordTree(root, tmpword);
            }
        }
        else continue;
    }
   fclose(fp);
}
int main(int argc,char *argv[])
{
    struct tnode* root=(struct tnode*)malloc(sizeof(struct tnode));
    root->weight=0;root->isword=0;root->isleaf=0;root->visited=0;
    for(int i=0;i<26;i++)root->ptr[i]=NULL;

    GetStopWords();
    BuildTree(root);
    root0=root;
    TraverseTree(root);
    qsort(VecTor,n,sizeof(VecTor[0]),cmp);//权重从大到小，字典序从小到大
    for(int i=0;i<n;i++){
        printf("%s %d\n",VecTor[i].word,VecTor[i].weight);
    }
    return 0;
}
//字典树和hash都是查找结构，是服务于查找的快速算法，实现其他功能均比较消耗时间，在此解法中想要遍历tire树的想法比较不好
//想要得到单词明明可以存入trie树时就存入一个对应的数组变量，从trie中遍历读取反而会消耗时间


