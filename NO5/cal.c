#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
/**************************   构建表达式树的函数      ******************/
typedef struct TreeNode{  //树的结构体
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}Tree,*Treep;

Treep TreeStack[2021],tmp,p,q;  //树栈
int OpStack[2021];              //运算符栈
int treeTop=0,opTop=0;

void  pushOp( int *s,  int item ) //运算符栈压栈
{
    s[opTop]=item;
    opTop++;
}
void  pushTree( Treep *s,  Treep item )//树栈压栈
{
    s[treeTop]=item;
    treeTop++;
}
int popOp( int *s)//运算符栈弹栈
{
    return s[--opTop];
}
Treep popTree( Treep *s)//树栈弹栈
{
    Treep p=(Treep)malloc(sizeof(Tree));
    memcpy(p, s[treeTop-1], sizeof(struct TreeNode));  //复制树节点信息
    s[treeTop-1]=NULL;  //把树栈里的弹出的节点清空
    treeTop--;
    return p;
}
int GetOpTop(int *s )  //获得运算符栈的栈顶元素
{
    return s[opTop-1];
}
int GetTreeTop(Treep *s ) //获得树栈的栈顶元素
{
    return s[treeTop-1]->val;
}
Treep CreateLeaves(int item)  //生成一个新的叶子节点
{
    Treep q=(Treep)malloc(sizeof(Tree));
    q->left=NULL;
    q->right=NULL;
    q->val=item;
    return q;
}
int IsTheta(char c) //判断是否为运算符，是运算符返回1，若不是返回0
{
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '=':
            return 1;
        default:
            return 0;
    }
}
char Precede(char theta1,char theta2)   //运算符优先级比较，相当于存了一张符号表
{
    int i,j;
    char pre[7][7]={// +   -   *   /   (   )   =
            {'>','>','<','<','<','>','>'},
            {'>','>','<','<','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'<','<','<','<','<','=','0'},
            {'>','>','>','>','0','>','>'},
            {'<','<','<','<','<','0','='}};

    switch(theta1){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '=': i=6; break;
    }

    switch(theta2){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '=': j=6; break;
    }
    return(pre[i][j]);
}
int Operate(int a,char theta,int b)    //运算符含义表达
{
    int result;

    switch(theta){
        case'+':return a+b;
        case'-':return a-b;
        case'*':return a*b;
        case'/':             //判断除数是否为0，若除数为零返回错误提示，比较漂亮
            if(b!=0)
                return a/b;
            else
            {
                printf("Divisor can not Be zero!\n");
                exit(0);
            }
    }

}

//*************************************************构建表达式树

void CreateExpressionTree(char *expression)
{
    int theta,X1,X2;
    Treep a,b,tmp;
    char ch;
    int i=0;
    pushOp(OpStack,'=');
    ch=expression[i++];		// ch 读取表达式的下一个字符
    while(ch!='='|| GetOpTop(OpStack)!='=')
    {
        if(IsTheta(ch)) //判断是否为运算符
        {
            switch(Precede(GetOpTop(OpStack),ch)) // 比较 ch 和栈顶运算符的优先级
            {
                case'<':
                    pushOp(OpStack,ch);
                    ch=expression[i++];
                    break;
                case'>':
                    theta=popOp(OpStack);
                    p=CreateLeaves(theta);
                    b=popTree(TreeStack);//弹出两个，与新的的节点形成一个子树（倒三角）
                    a=popTree(TreeStack);
                    p->left=(Treep)malloc(sizeof(Tree));
                    p->right=(Treep)malloc(sizeof(Tree));
                    memcpy(p->left, a, sizeof(struct TreeNode));
                    memcpy(p->right, b, sizeof(struct TreeNode));
                    pushTree(TreeStack,p);
                    break;
                case'=':
                    popOp(OpStack);
                    ch=expression[i++]; //读取下一位字符并将指针向后偏移一位
                    break;
            }

        }
        else if(isdigit(ch)) //判断是否为数字
        {
            X1=ch-'0'; //将字符形式转化为数字
            p=CreateLeaves(X1);
            pushTree(TreeStack,p);
            X2=X1;
            ch=expression[i++]; //读取下一位字符并将指针向后偏移一位

            while(isdigit(ch)) //判断下一位是否还是数字
            {
                X1=ch-'0';
                X2=10*X2+X1; //归并至X2
                tmp=popTree(TreeStack);
                p=CreateLeaves(X2);
                pushTree(TreeStack,p);
                ch=expression[i++]; //读取下一位字符并将指针向后偏移一位
            }
        }
        else if(ch==' ') //判断是否为空格
        {
            while(ch==' ')
            {
                ch=expression[i++];
            }
        }
        else //出现非法字符
        {
            printf("Input has illegal characters!\n");
            printf("Please enter again.\n");
            exit(0); //返回错误提示
        }
    }

}
int EvaluateExpression(Treep T)
{
    if(T->left&&T->right)
    {
        if(T->left->left||T->left->right)
            EvaluateExpression(T->left);
        if(T->right->left||T->right->right)
            EvaluateExpression(T->right);

        T->val=Operate(T->left->val,T->val,T->right->val);
        free(T->left);
        free(T->right);
        T->left=T->right=NULL;
        return T->val;
    }
    return T->val;
}
void VISIT(Treep t)  //访问树节点
{
    if(t->val=='/' || t->val=='+' ||t->val=='-' ||t->val=='*')	printf("%c ",t->val);//结点存储符号还是数字靠特判处理
    else printf("%d ",t->val);
}
void PrintTree(Treep root)  //打印树节点信息
{
    if(root==NULL) printf("\n");
    else
    {
        VISIT(root);
        if(root->left!=NULL)
            VISIT(root->left);
        if(root->right!=NULL)
            VISIT(root->right);
        printf("\n");
    }
}
int main()
{
    char expression[2021];
    gets(expression);
    CreateExpressionTree(expression);
    PrintTree(TreeStack[0]);
    printf("%d\n",EvaluateExpression(TreeStack[0]));
    return 0;
}
