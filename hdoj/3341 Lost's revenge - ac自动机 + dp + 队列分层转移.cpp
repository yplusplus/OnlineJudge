#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "queue"
using namespace std;
const int kind = 4;
const int maxn = 510;
int root, tot, n;
int w[256], mask[5], cnt[4];
int dp[15000][510];
bool visit[15000];
char s[50];
int que[maxn];
struct Node {
    int child[4], fail, id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = id = 0;
    }
} T[maxn];
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s) {//插入单词
    int p = root, index;
    while (*s) {
        index = w[*s];
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].id++;
}
void build_ac_auto() {
    int head = 0, tail = 0;
    que[tail++] = root;
    while (head < tail) {
        int u = que[head++];
        for (int i = 0; i < kind; i++) {
            if (T[u].child[i]) {
                int son = T[u].child[i];
                int p = T[u].fail;
                if(u) {
                    T[son].fail = T[p].child[i];
                    T[son].id += T[T[p].child[i]].id;
                }
                que[tail++] = son;
            } else {//trie图，设定虚拟节点
                int p = T[u].fail;
                T[u].child[i] = T[p].child[i];
            }
        }
    }
}

void solve() {
    memset(visit, false, sizeof(visit));
    memset(dp, -1, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; s[i]; i++) cnt[w[s[i]]]++;
    for(int i = 4; i >= 0; i--) {
        if(i == 4) mask[i] = 1;
        else mask[i] = mask[i+1] * (cnt[i] + 1);
    }
    int ans = 0;
    dp[0][0] = 0;
    queue<int> que;
    que.push(0);
    visit[0] = true;
    while(!que.empty()) {
        int m = que.front();
        que.pop();
        for(int i = 0; i <= tot; i++) {
            if(dp[m][i] == -1) continue;
            for(int j = 0; j < 4; j++) {
                int k = m % mask[j] / mask[j+1];
                if(k >= cnt[j]) continue;
                k = T[i].child[j];
                int mm = m + mask[j+1];
                if(dp[mm][k] < dp[m][i] + T[k].id) {
                    dp[mm][k] = dp[m][i] + T[k].id;
                    ans = max(ans, dp[mm][k]);
                    if(!visit[mm]) {
                        que.push(mm);
                        visit[mm] = true;
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    w['A'] = 0, w['C'] = 1, w['G'] = 2, w['T'] = 3;
    int Case = 1;
    while(scanf("%d", &n)) {
        if(n == 0) break;
        init();
        for(int i = 0; i < n; i++) {
            scanf("%s", s);
            insert(s);
        }
        build_ac_auto();
        scanf("%s", s);
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
