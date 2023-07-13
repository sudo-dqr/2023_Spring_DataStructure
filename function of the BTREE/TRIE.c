#include<stdio.h>
//实现trie树结构
typedef struct Trie {
    struct Trie* children[26];
    int isEnd;
} Trie;
//创建树节点
Trie* trieCreate() {
    Trie* ret = malloc(sizeof(Trie));
    memset(ret->children, 0, sizeof(ret->children));
    ret->isEnd = 0;
    return ret;
}
//插入单词
void trieInsert(Trie* obj, char* word) {
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            obj->children[ch] = trieCreate();
        }
        obj = obj->children[ch];
    }
    obj->isEnd = 1;
}
//在树中查找单词
int  trieSearch(Trie* obj, char* word) {
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            return 0;
        }
        obj = obj->children[ch];
    }
    return obj->isEnd;
}
//在树中查找前缀
int trieStartsWith(Trie* obj, char* prefix) {
    int n = strlen(prefix);
    for (int i = 0; i < n; i++) {
        int ch = prefix[i] - 'a';
        if (obj->children[ch] == NULL) {
            return 0;
        }
        obj = obj->children[ch];
    }
    return 1;
}
//free trie树
void trieFree(Trie* obj) {
    for (int i = 0; i < 26; i++) {
        if (obj->children[i]) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}
//替换单词 将句子中的继承词替换为相应的字典中的词根
typedef struct Trie {
    int isEnd;
    struct Trie *children[26];
} Trie;

Trie * creatTrie() {
    Trie *node = (Trie *)malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->isEnd = 0;
    return node;
}

void freeTrie(Trie *root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
}
char *findRoot(const char *word, Trie *trie) {
    char *root = (char *)malloc(sizeof(char) * 1000);
    Trie *cur = trie;
    int len = strlen(word);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        char c = word[i];
        if (cur->isEnd) {
            root[pos] = 0;
            return root;
        }
        if (!cur->children[c - 'a']) {
            free(root);
            return word;
        }
        root[pos++] = c;
        cur = cur->children[c - 'a'];
    }
    root[pos] = 0;
    return root;
}
char ** split(char *str, char ch, int *returnSize) {
    int len = strlen(str);
    char **res = (char **)malloc(sizeof(char *) * len);
    int i = 0, pos = 0;
    while (i < len) {
        while (i < len && str[i] == ch) {
            i++;
        }
        int start = i;
        while (i < len && str[i] != ch) {
            i++;
        }
        if (start < len) {
            res[pos] = (char *)malloc(sizeof(char) * (i - start + 1));
            memcpy(res[pos], str + start, sizeof(char) * (i - start));
            res[pos][i - start] = '\0';
            pos++;
        }
    }
    *returnSize = pos;
    return res;
}
char * replaceWords(char ** dictionary, int dictionarySize, char * sentence){//主函数
    Trie *trie = creatTrie();
    for (int i = 0; i < dictionarySize; i++) {
        Trie *cur = trie;
        int len = strlen(dictionary[i]);
        for (int j = 0; j < len; j++) {
            char c = dictionary[i][j];
            if (!cur->children[c - 'a']) {
                cur->children[c - 'a'] = creatTrie();
            }
            cur = cur->children[c - 'a'];
        }
        cur->isEnd = 1;
    }
    int wordsSize = 0, pos = 0;
    char **words = split(sentence, ' ', &wordsSize);
    char *ans = (char *)malloc(sizeof(char) * (strlen(sentence) + 2));
    for (int i = 0; i < wordsSize; i++) {
        char * ret = findRoot(words[i], trie);
        pos += sprintf(ans + pos, "%s ", ret);
        free(words[i]);
        if (ret != words[i]) {
            free(ret);
        }
    }
    ans[pos - 1] = '\0';
    freeTrie(trie);
    return ans;//返回更改后的字符串
}