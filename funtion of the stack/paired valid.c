#include<stdio.h>
#include<string.h>
    char pairs(char a) {
        if (a == '}') return '{';
        if (a == ']') return '[';
        if (a == ')') return '(';
        return 0;
    }
    int isValid(char* s) {
        int n = strlen(s);
        if (n % 2 == 1) {
            return 0;
        }
        int stk[n + 1], top = 0;//变长数组有一定隐患
        for (int i = 0; i < n; i++) {
            char ch = pairs(s[i]);
            if (ch) {
                if (top == 0 || stk[top - 1] != ch) {
                    return 0;
                }
                top--;
            } else {
                stk[top++] = s[i];
            }
        }
        return top == 0;
    }

