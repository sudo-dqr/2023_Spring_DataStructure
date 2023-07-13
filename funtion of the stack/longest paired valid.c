//计算只包括小括号的序列()的最大连续匹配长度
//算法思路是用栈来记录下标
#include<string.h>
  int longestValidParentheses(char * s){
        int len=strlen(s),max=0;
        int stack[len+1];
        stack[0]=-1;
        for(int i=0,top=0;i<len;i++){
            if(s[i]=='('){
                stack[++top]=i;//左括号的下标入栈
            }
            else{//是右小括号
                top--;//先出栈
                if(top==-1){//是空栈
                    stack[++top]=i;//记录不匹配右括号下标
                }
                else{
                    max=max>=i-stack[top]?max:i-stack[top];//当前减去上一个不匹配的右括号位置
                }
            }
        }
        return max;
    }

