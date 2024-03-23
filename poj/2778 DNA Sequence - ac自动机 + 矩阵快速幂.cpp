#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define ll long long
const ll MOD = 100000;
const int kind = 4;
const int maxn = 500;
#define MAX 105
int root, tot;
int n, m;
int que[maxn], head, tail;
bool visit[maxn];
struct Node {
    int child[kind];
    int fail;
    int end;
    void init() {
        memset(child, 0, sizeof(child));
        fail = -1, end = 0;
    }
} T[maxn];

void init() {
    root = tot = 0;
    T[root].init();
}

int hash(char ch) {
	if(ch == 'A') return 0;
	else if(ch == 'C') return 1;
	else if(ch == 'G') return 2;
	else return 3;
}

void insert(char *s) {//插入单词
    int p = root, index;
    while (*s) {
        index = hash(*s);
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
	T[p].end = 1;
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
				else {
					T[son].fail = T[p].child[i];
					T[son].end |= T[T[son].fail].end;
				}
                que[tail++] = son;
            } else {//trie图，设定虚拟节点
                int p = T[u].fail;
                if (u == root) T[u].child[i] = root;
				else T[u].child[i] = T[p].child[i];
            }
        }
    }
}

struct Mat {
	ll val[MAX][MAX];
	void unit() {
		zero();
		for(int i = 0; i < MAX; i++) val[i][i] = 1;
	}
	void zero() {
		memset(val, 0, sizeof(val));
	}
}x;

Mat operator *(const Mat &a, const Mat &b) {
	Mat tmp;
	tmp.zero();
	for(int k = 0; k <= tot; k++) {
		for(int i = 0; i <= tot; i++) {
			if(a.val[i][k])
				for(int j = 0; j <= tot; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= MOD) tmp.val[i][j] %= MOD;
				}
		}
	}
	return tmp;
}

Mat operator ^(Mat x, int n) {
	Mat tmp;
	tmp.unit();
	while(n) {
		if(n & 1) tmp = tmp * x;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

void dfs(int u) {
	visit[u] = true;
	for(int i = 0; i < kind; i++) {
		int v = T[u].child[i];
		if(!T[v].end) {
			x.val[u][v]++;
			if(!visit[v]) dfs(v);
		}
	}
}

int main() {
	char s[15];
	while(~scanf("%d%d", &m, &n)) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%s", s);
			insert(s);
		}
		build_ac_auto();
		x.zero();
		memset(visit, false, sizeof(visit));
		dfs(root);
		Mat ans = x ^ n;
		ll res = 0;
		for(int i = 0; i <= tot; i++)
			res += ans.val[0][i];
		printf("%lld\n", res % MOD);
	}
	return 0;
}