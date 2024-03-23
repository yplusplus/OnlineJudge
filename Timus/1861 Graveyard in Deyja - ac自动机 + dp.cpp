#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int kind = 52;
const int maxn = 1010;
int root, tot;
int id[128];
char s1[1010], s2[1010];
int dp[1010][1010];
struct Node {
    int child[kind];
    int fail;
    int id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = -1, id = 0;
    }
} T[maxn];
int que[maxn], head, tail;
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s) {//插入单词
    int p = root, index;
    while (*s) {
        index = id[*s];
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].id = 1;
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

int main() {
    for(char i = 'A'; i <= 'Z'; i++) id[i] = i - 'A';
    for(char i = 'a'; i <= 'z'; i++) id[i] = i - 'a' + 26;
    while(~scanf("%s%s", s1, s2)) {
        int l1 = strlen(s1);
        int l2 = strlen(s2);
        init();
        insert(s2);
        build_ac_auto();
        for(int i = 0; i < 1010; i++)
            for(int j = 0; j < 1010; j++)
                dp[i][j] = -1;
        dp[0][0] = 0;
        for(int i = 0; i < l1; i++) {
            for(int j = 0; j <= l2; j++) {
                if(dp[i][j] == -1) continue;
                if(s1[i] == '?') {
                    for(int k = 0; k < 52; k++) {
                        int son = T[j].child[k];
                        dp[i+1][son] = max(dp[i+1][son], dp[i][j] + T[son].id);
                    }
                } else {
                    int son = T[j].child[id[s1[i]]];
                    dp[i+1][son] = max(dp[i+1][son], dp[i][j] + T[son].id);
                }
            }
        }
        int ans = 0;
        for(int i = 0; i <= tot; i++) ans = max(ans, dp[l1][i]);
        cout << ans << endl;
    }
    return 0;
}
