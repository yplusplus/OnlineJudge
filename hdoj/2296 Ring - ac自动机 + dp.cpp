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
#define maxm 110
const int kind = 26;
const int maxn = 5000;
int root, tot;
char s[maxm][15];
int val[maxm];
int n, m;
int dp[55][1010];
struct Node {
    int child[kind];
    int fail;
    int score;
    void init() {
        memset(child, 0, sizeof (child));
        fail = -1, score = 0;
    }
} T[maxn];
int que[maxn], head, tail;
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s, int score) {//插入单词
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
    T[p].score = score;
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
                    T[son].score += T[T[p].child[i]].score;
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

string t[maxm][1010];
int main() {
    int TT;
    scanf("%d", &TT);
    while(TT-- ) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) scanf("%s", s[i]);
        for(int i = 0; i < m; i++) scanf("%d", &val[i]);
        init();
        for(int i = 0; i < m; i++) {
            insert(s[i], val[i]);
        }
        build_ac_auto();
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;
        for(int i = 0; i <= tot; i++) t[0][i] = "";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= tot; j++) {
                if(dp[i][j] == -1) continue;
                for(int k = 0; k < kind; k++) {
                    int son = T[j].child[k];
                    int w = dp[i][j] + T[son].score;
                    char ch = k + 'a';
                    if(dp[i+1][son] < w) {
                        dp[i+1][son] = w;
                        t[i+1][son] = t[i][j] + ch;
                    } else if(dp[i+1][son] == w) {
                        string tmp = t[i][j] + ch;
                        if(tmp < t[i+1][son]) t[i+1][son] = tmp;
                    }
                }
            }
        }
        string ans_str;
        int ans = 0, len = 0;
        for(int i = 0; i <= n; i++)
           for(int j = 0; j <= tot; j++) {
               if(ans < dp[i][j]) {
                  ans_str = t[i][j];
                  ans = dp[i][j];
                  len = i;
              } else if(ans == dp[i][j] && len == i && t[i][j] < ans_str) {
                  ans_str = t[i][j];
              }
           }
        cout << ans_str << endl;
    }
    return 0;
}
