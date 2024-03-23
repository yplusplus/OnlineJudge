#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int kind = 4;
const int maxn = 250;
int score[15];
int root, tot;
char ch[25];
int n, m, l;
int que[maxn], head, tail;

struct Node {
    int child[kind];
    int fail;
    int id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = -1, id = 0;
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

void insert(char *s, int id) {//插入单词
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
    T[p].id |= 1 << id;
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
					T[son].id |= T[T[son].fail].id;
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
bool dp[2][205][1<<10];//滚动数组,不用滚动也可以
void solve() {
	int mask = 1 << n, now, next;
	memset(dp, false, sizeof(dp));
	dp[0][0][0] = true;
	for(int i = 0; i < l; i++) {
		now = i % 2;
		next = (i + 1) % 2;
		memset(dp[next], false, sizeof(dp[next]));
		for(int j = 0; j <= tot; j++) {
			for(int k = 0; k < mask; k++) {
				if(dp[now][j][k]) {
					for(int p = 0; p < kind; p++) {
						int son = T[j].child[p];
						dp[next][son][k|T[son].id] = true;
					}
				}
			}
		}
	}
	int ans = -(1 << 30);
	now = l % 2;
	for(int i = 0; i <= tot; i++) {
		for(int j = 0; j < mask; j++) {
			if(dp[now][i][j]) {
				int t = 0;
				for(int k = 0; k < n; k++) {
					if(j & (1<< k)) t += score[k];
				}
				ans = max(ans, t);
			}
		}
	}
	if(ans < 0) printf("No Rabbit after 2012!\n");
	else printf("%d\n", ans);
}

int main() {
	while(~scanf("%d%d", &n, &l)) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%s%d", ch, &score[i]);
			insert(ch, i);
		}
		build_ac_auto();
		solve();
	}
	return 0;
}