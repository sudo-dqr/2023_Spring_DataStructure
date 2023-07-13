#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node
{
    char s[1024];
    struct node *lchild,*rchild;
    int cnt;
}BTNode,*BTNodeptr;
BTNodeptr root=NULL;
int getword(FILE *fp,char *w)
{
    int c;
    while(!isalpha(c=fgetc(fp)))
    if(c==EOF)return c;
    else continue;
    do{
        *w++=tolower(c);
    }while(isalpha(c=fgetc(fp)));
    *w='\0';
    return 1;
}
void insertnode(char*word)
{
   BTNodeptr p,q;
   p=(BTNodeptr)malloc(sizeof(BTNode));
   strcpy(p->s,word);
   p->cnt=1;
   p->lchild=p->rchild=NULL;
   if(root==NULL)
    root=p;
    else{
        q=root;
        while(1){
            if(strcmp(word,q->s)<0)
            {
                if(q->lchild==NULL)
                {
                q->lchild=p;
                break;
                }
                else q=q->lchild;
            }
        else if(strcmp(word,q->s)>0)
        {
            if(q->rchild==NULL)
            {
                q->rchild=p;
                break;
            }
            else q=q->rchild;
        }
        else 
        {
            q->cnt++;
            break;
        }
     }
    }
}
void printbtnode(BTNodeptr t)
{
     if(t!=NULL)
    {
     printbtnode(t->lchild);
     printf("%s %d\n",t->s,t->cnt);
     printbtnode(t->rchild);
    }
}
int main()
{
    FILE* fp=fopen("article.txt","r");
    char word[1024]="0";
    while(getword(fp,word)!=EOF)
    {
           insertnode(word);
    }
    fclose(fp);
    BTNodeptr q=root;
    while(1)
    {
         printf("%s",q->s);
         q=q->rchild;
        if(q!=NULL)
        {
            printf(" ");
        }
        if(q==NULL)
        {
            printf("\n");
            break;
        }
    }
   printbtnode(root);
    return 0;
}