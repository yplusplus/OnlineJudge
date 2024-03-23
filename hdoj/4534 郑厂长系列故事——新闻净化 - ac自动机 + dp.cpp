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
const int N = 111;
const int M = 1666;
pii dp[2][M][1 << 8];
const int kind = 26;
int root, tot;
int que[M];
int n;
struct Node {
    int child[kind], fail, score, id;
    bool banned;
    void init() {
        memset(child, 0, sizeof(child));
        fail = id = score = 0;
        banned = false;
    }
}T[M];

void init() {
    root = tot = 0;
    T[root].init();
}

void insert(char *s, bool banned, int score, int id) {//²åÈëµ¥´Ê
    int p = root;
    while (*s) {
        int index = *s - 'a';
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].banned |= banned;
    T[p].id = id;
    T[p].score += score;
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
                    T[son].score += T[T[p].child[i]].score;
                    T[son].banned |= T[T[p].child[i]].banned;
                }
                que[tail++] = son;
            } else {
                int p = T[u].fail;
                T[u].child[i] = T[p].child[i];
            }
        }
    }
}

void update(pii &dp, int cnt, int score) {
    if (dp.fi > cnt || (dp.fi == cnt && dp.se < score)) {
        dp = mp(cnt, score);
    }
}

int main() {
    int Test, Case = 1;
    cin >> Test;
    char str[N];
    while (Test--) {
        init();
        cin >> n;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int score;
            scanf("%s%d", str, &score);
            if (score == 999) insert(str, false, 0, 1 << cnt);
            else if (score == -999) insert(str, true, 0, 0);
            else insert(str, false, score, 0);
            cnt += score == 999;
        }
        scanf("%s", str + 1);
        build_ac_auto();
        int all = 1 << cnt;
        int len = strlen(str + 1);
        for (int j = 0; j <= tot; j++) {
            for (int k = 0; k < all; k++) {
                dp[0][j][k] = mp(inf, -inf);
            }
        }
        dp[0][0][0] = mp(0, 0);
        for (int i = 0; i <= len; i++) {
            int p = i & 1;
            for (int j = 0; j <= tot; j++) {
                for (int k = 0; k < all; k++) {
                    dp[p ^ 1][j][k] = mp(inf, -inf);
                }
            }
            int index = str[i+1] - 'a';
            for (int j = 0; j <= tot; j++) {
                for (int k = 0; k < all; k++) {
                    //delete
                    update(dp[p ^ 1][j][k], dp[p][j][k].fi + 1, dp[p][j][k].se);
                    // not delete
                    int son = T[j].child[index];
                    if (T[son].banned) continue;
                    update(dp[p ^ 1][son][k | T[son].id], dp[p][j][k].fi, dp[p][j][k].se + T[son].score);
                }
            }
        }
        pii ans = mp(inf, -inf);
        for (int i = 0; i <= tot; i++) {
            update(ans, dp[(len + 1) & 1][i][all - 1].fi, dp[(len + 1) & 1][i][all - 1].se);
        }
        printf("Case %d: ", Case++);
        if (ans.fi == inf) {
            puts("Banned");
        } else {
            printf("%d %d\n", ans.fi, ans.se);
        }
    }
    return 0;
}
