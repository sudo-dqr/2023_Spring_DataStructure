#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//压缩 txt->hzip 解压hzip->txt
typedef struct tnode{
    char ch;
    int weight;
    struct tnode*lchild,*rchild;
}Tnode,*Tnodeptr;
Tnodeptr  root=NULL;
Tnodeptr  forest[1000]={0};
int CheckFile(int ,char *[],char *,char *);
char *getPosname(char []);
void getch(FILE* );
int GrowForest(Tnodeptr []);
void BubbleSort(Tnodeptr [],int );
Tnodeptr BuildhuffmanTree(Tnodeptr [],int  );
void insertnode(Tnodeptr [],int n,Tnodeptr);
void makeCode(Tnodeptr ,char ,int );
//void transform(FILE * ,FILE *);
void makeHZip(FILE* src, FILE* zip);
void saveFileHead(FILE* zip);
char Ccount[128]={0};
char HuffmanCode[128][100];
int  hcodelength=0;
int main(int argc,char *argv[]){//argc代表传入参数个数，argv指针数组指向传入的参数,这里需要注意的是在不输入命令行参数时，argc初始值为1,表示只有一个文件名称，argc[0]指向程序路径及名称
   FILE* src;FILE *dst;
   char srcFileName[50]="0",dstFlieName[50]="0";
   int op= CheckFile(argc,argv,srcFileName,dstFlieName);
   if(op==0)return 0;
   else if(op==1){//压缩功能
       src=fopen(srcFileName,"r");
       if(src==NULL)
       {
           printf("can't open the file!");
           exit(-1);
       }
           char *p= getPosname(dstFlieName);
           strcpy(p,"hzip");//修改目标文件的扩展名；
           dst=fopen(dstFlieName,"w");
           if(dst==NULL)
           {
               printf("can't open the file!");
               exit(-1);
           }
           getch(src);
           int cnt=GrowForest(forest);
           BuildhuffmanTree(forest,cnt);
           root=forest[0];//huffman树建立完成
          makeCode(root,'\0',0);
          fseek(src,0,SEEK_SET);//将src置回文件头
            makeHZip(src, dst);
           fclose(dst);
           fclose(src);
   }
   else if(op==2){//解压功能

   }
   return 0;
}
void BubbleSort(Tnodeptr s[],int n)
{
    int  swap_flag=0,i,j;
    Tnodeptr temp=NULL;
    for(i=1;i<=(n-1);i++){
        for(j=0;j<(n-i);j++){
            if(s[j]->weight>s[j+1]->weight){
                swap_flag=1;
                temp=s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }else if(s[j]->weight==s[j+1]->weight)
            {
                if(s[j]->ch>s[j+1]->ch)
                {
                    swap_flag=1;
                    temp=s[j];
                    s[j]=s[j+1];
                    s[j+1]=temp;
                }
            }
        }
        if(swap_flag==0){
            break;
        }
    }
}
void getch(FILE* src)
{
    int ch;
    Ccount[0]=1;
    while(ch=fgetc(src)){
        if(ch==EOF){
            break;
        }
        if(ch=='\n')continue;
        Ccount[ch]++;
    }
}
char *getPosname(char *s)//找到文件中的后缀名
{
   char *p=strchr(s,'.');
   return p+1;
}
int CheckFile(int cnt,char *params[],char *srcfile,char *dstflie)
{
//cnt代表命令行参数中传入的参数的个数，当输入压缩指令时，hzip myfile.txt 会被处理为两个字符串，
//当输入解压指令时，会被处理为三个字符串  hzip -u myflie.hzip
    if(cnt==2){//缺少参数
       printf("Usage:hzip.exe[-u]<fliename>");
       return 0;
   }
   if(cnt==3)//压缩
   {
       //检查文件类型txt
       char *temp=getPosname(params[2]);
       if(strcmp(temp,"txt")!=0) {
           printf("Flie extension error!");
           return 0;
       }
       else {
           strcpy(srcfile,params[2]);
           strcpy(dstflie,srcfile);
           return 1;
       }
   }
   if(cnt==4){
       if(strcmp(params[2],"-u")!=0){
           printf("Usage:hzip.exe[-u]<fliename>");
       }
       char *temp= getPosname(params[3]);
       if(strcmp(temp,"hzip")!=0) {
           printf("Flie extension error");
           return 0;
       }
       else{
           strcpy(srcfile,params[3]);
           strcpy(dstflie,srcfile);
           return 2;
       }
   }
   return 0;
}
int GrowForest(Tnodeptr s[])
{
    int i=0,pos=0;
    for(;i<128;i++){
        if(Ccount[i]>0){
            hcodelength++;
            Tnodeptr p=(Tnodeptr)malloc(sizeof(Tnode));
            p->ch=i;
            p->weight=Ccount[i];
            p->rchild=p->lchild=NULL;
            s[pos++]=p;
        }
    }
    BubbleSort(s,pos);
    return pos;
}
void insertnode(Tnodeptr s[],int n,Tnodeptr p)
{
    int i=0,j=0;
    n=n-2;
    for(;i<n;i++)s[i]=s[i+2];
    i=0;
    while(p->weight>=s[i]->weight&&i<n)i++;
    for(j=n-1;j>=i;j--)s[j+1]=s[j];
    s[i]=p;
}
Tnodeptr BuildhuffmanTree(Tnodeptr s[],int n)
{
    while(n>1)
    {
        Tnodeptr p=(Tnodeptr)malloc(sizeof(Tnode));
        p->weight=s[0]->weight+s[1]->weight;
        p->lchild=s[0],p->rchild=s[1];
        insertnode(s,n,p);
        n--;
    }
}
char s[100]="0";//千万注意临时数组在递归函数外声明，否则递归调用时重新声明，前功尽弃
void makeCode(Tnodeptr root,char code,int level)//level表示深度 code表示向左向右01
{
    if(level!=0)s[level-1]=code;
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        s[level]='\0';
        strcpy(HuffmanCode[root->ch],s);
    }
    else{
        makeCode(root->lchild,'0',level+1);
        makeCode(root->rchild,'1',level+1);
    }
}

void makeHZip(FILE* src, FILE* zip) {//将文件内容写入压缩文件(是可以直接写入hzip文件的)
    char* pc;//用于访问哈夫曼编码中字符串的0、1位
    unsigned char hc = 0;//用于生成8位二进制位，不需要符号位
    int ch = 0, codeLen = 0;
    saveFileHead(zip); //先写入压缩文件头信息
    fseek(src, 0, SEEK_SET);//将文件读写指针移到开头
    do { ch = fgetc(src);//读取文件中的字符
        if (ch == EOF) ch = 0;//如果文件结束，则将ascii设置0,表示压缩文件结束
        pc = HuffmanCode[ch];//拿到单个字符的哈夫曼编码
        for (; *pc != '\0'; pc++) {//将"110"这样字符串转换为对应的二进制0、1位，存储到hc中
            hc = (hc << 1) | (*pc - '0');//根据当前字符'0'、'1'，修改hc的最后一位为二进制0、1
            codeLen++;//记录当前已经存储了多少位有效的二进制位
            if (codeLen == 8) {//如果存满8位，即生成一个完整字节，则写入文件
                fputc(hc, zip); //生成的8位二进制（即一个字节）写入压缩文件
                codeLen = 0;
            } }
        if (ch == 0 && codeLen != 0) {//最后一个字符不满8位，不够一个字节
            while (codeLen++ < 8) hc = (hc << 1);//后面移入若干个0，补满8位
            fputc(hc, zip);
        }
    } while (ch);
}
void saveFileHead(FILE* zip) {//生成ascII与huffman对照表
    int i = 0, len; unsigned char hc=0; char* pc; int codeLen = 0;
    fseek(zip, 0, SEEK_SET);//将文件读写指针移到开头
    fputc(hcodelength, zip);//写入码表长度
    for (i = 0; i < 128; i++) {
        pc = HuffmanCode[i]; len = strlen(pc);
        if (len > 0) {//如果存在该字符的哈夫曼编码
            fputc(i, zip);//写入字符信息
            fputc(len, zip); //写入哈夫曼编码长度信息
            codeLen = 0; hc = 0;
            for (; *pc != '\0'; pc++) {//将"110"这样字符串转换为对应的二进制0、1位，存储到hc中
                hc = (hc << 1) | (*pc - '0');//根据当前字符'0'、'1'，修改hc最后一位为二进制0、1
                codeLen++;//记录当前已经存储了多少位有效的二进制位
                if (codeLen == 8) {//如果存满8位，即生成一个完整字节，则写入文件
                    fputc(hc, zip); //生成的8位二进制（即一个字节）写入压缩文件
                    codeLen = 0;
                }
            }
            if (codeLen != 0) {//不满8位，不够一个字节
                while (codeLen++ < 8) hc = (hc << 1);//后面移入若干个0，补满8位
                fputc(hc, zip);
            } } } }

/*
 有关fseek函数
 在进行文件读写的过程中，存在一个指针，每次调用文件的读写函数该指针就会移动(从前向后)
文件内部指针的位置可以通过fseek改变
 int fseek(FLIE* stream,long offset,int fromwhere);
 设置的指针位置为起始位置+偏移量
 offset偏移量：正数表示向后，负数表示向前
 int fromwhere表示起始位置
 文件头 SEEK_SET 0
 当前位置 SEEK_CUR 1
 文件尾 SEEK_END 2
 在此程序中涉及到将指针移回文件头
 fseek(src,0,SEEK_SET);表示移动到距离文件头位移为0的位置
 fseek(src,1,SEEK_CUR)向后跳过一个字节
 */