#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 700050
const int kind = 26;
int root, tot;
int que[maxn], head, tail;
int n, m;
char t[1005000];

struct Node {
    int child[kind], fail, cnt;
    void init() {
        memset(child, 0, sizeof (child));
        fail = -1, cnt = 0;
    }
}T[maxn];

void init() {
    root = tot = 0;
    T[root].init();
}

void insert(char *s) {//插入单词
    int p = root, index;
    while (*s) {
        index = *s - 'a';
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].cnt++;
}

void build_ac_auto() {
    head = tail = 0;
    que[tail++] = root;
    while (head < tail) {
        int u = que[head++];
        for (int i = 0; i < kind; i++) {
            if (T[u].child[i]) {
                int son = T[u].child[i];
                int p = T[u].fail;
                if (u == root) T[son].fail = root;
                else T[son].fail = T[p].child[i];
                que[tail++] = son;
            } else {//trie图，设定虚拟节点
                int p = T[u].fail;
                if (u == root) T[u].child[i] = root;
                else T[u].child[i] = T[p].child[i];
            }
        }
    }
}

int query(char *t) {
	int p = root, cnt = 0;
	while(*t) {
		int index = *t - 'a';
		p = T[p].child[index];
		int tmp = p;
		while(tmp != root) {
			cnt += T[tmp].cnt;
			T[tmp].cnt = 0;
			tmp = T[tmp].fail;
		}
        t++;
	}
	return cnt;
}

int main() {
	int T;
	char s[55];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		init();
		for(int i = 0; i < n; i++) {
			scanf("%s", s);
			insert(s);
		}
		scanf("%s", t);
		build_ac_auto();
		int ans = query(t);
		printf("%d\n", ans);
	}
	return 0;
}