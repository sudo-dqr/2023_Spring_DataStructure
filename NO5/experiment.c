//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()//统计文件中字符出现频率,不处理换行符
{
    int ch;
    Ccount[0]=1;
    while(ch=fgetc(Src))
    {
        if(ch==EOF)
        break;
        if(ch=='\n')
        continue;
        Ccount[ch-'\0']++;
    }
}

//【实验步骤1】结束

//【实验步骤2】开始
void optiBubbleSort(struct tnode* forest[],int n){
 int  swap_flag=0;
	struct tnode* temp=NULL;
	for(int i=1;i<=(n-1);i++){
		for(int j=0;j<(n-i);j++){
			if(forest[j]->weight>forest[j+1]->weight){
				swap_flag=1;
			    temp=forest[j];
				forest[j]=forest[j+1];
				forest[j+1]=temp;
			}
            else if(forest[j]->weight==forest[j+1]->weight)
            {
                if(forest[j]->c>forest[j+1]->c)
                {
                    swap_flag=1;
			        temp=forest[j];
				    forest[j]=forest[j+1];
				    forest[j+1]=temp;
                }
            }
		}
		if(swap_flag==0){
			break;
		}	
	}	
}
void move(struct tnode*forest[],int cnt)//覆盖掉前两个结点
{
    int i=0;
    for(i=0;i<cnt-2;i++)
    forest[i]=forest[i+2];
}
void insert(struct tnode*forest[],struct tnode*p,int cnt)//有序插入节点
{
    int i=0,j=0;
    while((forest[i]->weight<=p->weight)&&(i<cnt-1))
    i++;
    for(j=cnt-1;j>=i;j--)
    forest[j+1]=forest[j];
    forest[i]=p;
}
void createHTree()
{
    int i,cnt=0;
    struct tnode* forest[10000];
    for(i=0;i<128;i++){
        if(Ccount[i]>0){
            struct tnode*p=(struct tnode*)malloc(sizeof(struct tnode));
            p->c=i,p->weight=Ccount[i];
            p->left=p->right=NULL;
            forest[cnt++]=p;
        }
    }
    optiBubbleSort(forest,cnt);
    while(cnt>1){
        struct tnode *p=(struct tnode*)malloc(sizeof(struct tnode));
        p->weight=forest[0]->weight+forest[1]->weight;
        p->left=forest[0],p->right=forest[1];
        move(forest,cnt);
        cnt--;
        insert(forest,p,cnt);
    }
    Root=forest[0];
}
//【实验步骤2】结束

//【实验步骤3】开始
//左边为0右边为1
char s[100];
void visitHtree(struct tnode* p,char code,int level)
{
    if(level!=0)s[level-1]=code;//记录路径
    if(p->left==NULL&&p->right==NULL){//叶子节点
        s[level]='\0';
        strcpy(HCode[p->c],s);
    }
    else{
        visitHtree(p->left,'0',level+1);
        visitHtree(p->right,'1',level+1);
    }
}
void makeHCode()
{
	visitHtree(Root,'\0',0);
} 

//【实验步骤3】结束

//【实验步骤4】开始
void makezip(FILE*src,FILE* obj)
{
    char *pc;
	unsigned char hc=0;
	int ch=0,codelen=0;
	do{
		ch=fgetc(src);
		if(ch==EOF)ch=0;//读到结束符将ch赋0
		pc=HCode[ch];
        for(;*pc!='\0';pc++){
			hc=(hc<<1)|(*pc-'0');
			codelen++;
			if(codelen==8){//存够八位输出
				fputc(hc,obj);
				printf("%x",hc);
				codelen=0;
			}
		}
		if(ch==0&&codelen!=0){
			while(codelen++<8)hc=(hc<<1);//对应着最后一位结束符'\0'
			fputc(hc,obj);
			printf("%x",hc);
		}
	}while(ch);//ch==0 break;
}
void atoHZIP()
{
   FILE* src=fopen("input.txt","r");
   FILE* obj=fopen("output.txt","w");
   makezip(src,obj);
  fclose(src);
   fclose(obj);
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小: %ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
