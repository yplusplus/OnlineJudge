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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int kind = 2;
const int N = 222;
int root, tot;
int que[N];
int w[256];
struct Node {
    int child[kind], fail, id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = id = 0;
    }
} T[N];
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s, int id) {
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
    T[p].id = id;
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
                    T[son].id |= T[T[p].child[i]].id;
                }
                que[tail++] = son;
            } else {
                int p = T[u].fail;
                T[u].child[i] = T[p].child[i];
            }
        }
    }
}

int dp[2][205][105][4];

const int MOD = 1000000007;
int add(int a, int b) {
    return (a + b) % MOD;
}

int main() {
    int r, c;
    w['D'] = 0;
    w['R'] = 1;
    char str[222];
    int Case;
    scanf("%d", &Case);
    while (Case--) {
        scanf("%d%d", &r, &c);
        int n = r + c;
        init();
        for (int i = 0; i < 2; i++) {
            scanf("%s", str);
            insert(str, 1 << i);
        }
        build_ac_auto();
        memset(dp[0], 0, sizeof(dp[0]));
        dp[0][0][0][0] = 1;
        //cout << tot << endl;
        for (int i = 0; i < n; i++) {
            memset(dp[~i & 1], 0, sizeof(dp[~i & 1]));
            for (int j = 0; j <= tot; j++) {
                for (int jj = 0; jj <= n && jj <= r; jj++) {
                    for (int k = 0; k < 4; k++) {
                        if (dp[i & 1][j][jj][k] == 0) continue;
                        for (int l = 0; l < kind; l++) {
                            int son = T[j].child[l];
                            dp[~i & 1][son][jj + l][k | T[son].id] = add(dp[~i & 1][son][jj + l][k | T[son].id], dp[i & 1][j][jj][k]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= tot; i++) {
            ans = add(ans, dp[n & 1][i][r][3]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
