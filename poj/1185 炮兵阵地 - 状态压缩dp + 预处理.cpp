#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 25;
int n, m;
char maz[110][15];
int row[110];
int dp[110][70][70];
int st[70], tot, cnt[70];

void init() {
    tot = 0;
    memset(cnt, 0, sof(cnt));
    int nn = 1 << m;
    for(int i = 0; i < nn; i++) {
        bool flag = true;
        int tmp = 0;
        for(int j = m - 1; j >= 0; j--) {
            if(i & (1 << j)) {
                tmp++;
                if((j >= 1) && (i & (1 << (j-1)))) {
                    flag = false;
                    break;
                }
                if((j >= 2) && (i & (1 << (j-2)))) {
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

void solve() {
    init();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < tot; j++)
            for(int k = 0; k < tot; k++)
                dp[i][j][k] = -inf;

    for(int i = 0; i < tot; i++) 
        if(!(st[i] & row[0])) 
            dp[0][i][0] = cnt[i];

    for(int i = 1; i < n; i++)
        for(int j = 0; j < tot; j++)
            if(!(row[i] & st[j])) 
                for(int k = 0; k < tot; k++)
                    if(!(st[j] & st[k]))
                        for(int kk = 0; kk < tot; kk++)
                            if(!(st[j] & st[kk]))
                                dp[i][j][k] = max(dp[i][j][k], cnt[j] + dp[i-1][k][kk]);

    int ans = 0;
    for(int i = 0; i < tot; i++)
        for(int j = 0; j < tot; j++)
            ans = max(ans, dp[n-1][i][j]);
    printf("%d\n", ans);
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        memset(row, 0, sof(row));
        for(int i = 0; i < n; i++) {
            scanf("%s", maz[i]);
            for(int j = m - 1; j >= 0; j--) {
                row[i] <<= 1;
                if(maz[i][j] == 'H') row[i] |= 1;
            }
        }
        solve();
    }
    return 0;
}
