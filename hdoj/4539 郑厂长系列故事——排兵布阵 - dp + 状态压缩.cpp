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
int row[N];
int dp[N][200][200];
int st[200], tot, cnt[200];
int n, m;
void init(int all) {
    tot = 0;
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < all; i++) {
        bool flag = true;
        int tmp = 0;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                tmp++;
                if (j + 2 < m && (i >> j >> 2 & 1)) {
                    flag = false;
                    break;
                }
            }
        }
        if(flag) {
            st[tot] = i, cnt[tot++] = tmp;
        }
    } 
}

bool check(int m1, int m2) {
    for (int i = 0; i < m; i++) {
        if (m1 >> i & 1) {
            if ((i + 1 < m) && (m2 >> (i + 1) & 1)) return false;
        }
    }
    return true;
}

bool check2(int m1, int m2) {
    return (m1 & m2) == 0;
}

void solve() {
    init(1 << m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < tot; j++)
            for(int k = 0; k < tot; k++)
                dp[i][j][k] = -inf;

    for(int i = 0; i < tot; i++) 
        if(!(st[i] & row[0])) 
            dp[0][i][0] = cnt[i];

    for(int i = 1; i < n; i++)
        for(int j = 0; j < tot; j++)
            if(check2(row[i], st[j])) 
                for(int k = 0; k < tot; k++)
                    if (check(st[j], st[k]) && check(st[k], st[j]))
                        for(int kk = 0; kk < tot; kk++)
                            if (check2(st[kk], st[j]))
                                dp[i][j][k] = max(dp[i][j][k], cnt[j] + dp[i-1][k][kk]);

    int ans = 0;
    for(int i = 0; i < tot; i++)
        for(int j = 0; j < tot; j++)
            ans = max(ans, dp[n-1][i][j]);
    printf("%d\n", ans);
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            row[i] = 0;
            for (int j = 0; j < m; j++) {
                int x;
                scanf("%d", &x);
                x ^= 1;
                row[i] |= x << j;
            }
        }
        solve();
    }
    return 0;
}
