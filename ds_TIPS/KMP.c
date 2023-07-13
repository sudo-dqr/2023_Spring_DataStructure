#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#define maxsize 100
/*
最长相等前缀与后缀
相等前后缀的最大长度为n-1;(字符串长度为n)
a b c a b |e a b c a b c m n
a b c a b |c m n
已经匹配的部分abcab,最长相等前后缀为"ab"
此时母串指向e,子串指向c;
KMP算法母串指向方向不变，将子串指向向后移动
字串移动的结果是让子串已经匹配部分的最长相等前缀和主串最长相等后缀部分对齐
a b c a b |e a b c a b c m n
      a b |c a b c m n
利用next数组存储已经匹配部分的最长相等前后缀的长度
next[i]=j;
代表着1.下标为i的字符前最长相等前后缀的长度
      2.该处字符不匹配时应该回溯到的下标
      //该处字符不匹配，子串移动到最长相等前缀的下一个字符
以"abcabcmn"为例
next[0]=-1;
next[1]=0;
next[2]=0;
next[3]=0;
next[4]=1;
next[5]=2;
next[6]=3;
next[7]=0;
*/
typedef struct
{
    char data[maxsize];
    int length;
}SqString;
void  GetNext(SqString t, int next[])//求解next数组函数
{
    int j, k;
    j = 0, k = -1;
    next[0] = -1;
    while (j < t.length - 1)
     //next数组下标j最大为t.length-1;每一步next数组赋值都是在j++之后
    {
        if (k == -1 || t.data[j] == t.data[k])
        {
            j++; k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
            // next[j] 
            //.下标为j的字符前最长相等前后缀的长度
             //   2.该处字符不匹配时应该回溯到的下标
        }
    }
}
int KMPIndex(SqString s, SqString t)
{
    int next[maxsize], i = 0, j = 0;
    GetNext(t, next);
    while (i < s.length && j < t.length)
    {
        if (j == -1 || s.data[i] == t.data[j])
        {
            i++; j++;
        }
        else
        {
            j = next[j];//母串匹配位置不变，子串位置回退
          
        }
    }
    if (j >= t.length)//走到子串末尾
        return i - t.length;//匹配模式串的首字符下标
    else
        return -1;//没有匹配
}
int main()
{
    SqString s, t;
    scanf("%s", s.data);
    scanf("%s", t.data);
    s.length = strlen(s.data);
    t.length = strlen(t.data);
    printf("%d", KMPIndex(s, t));
    return 0;
}
