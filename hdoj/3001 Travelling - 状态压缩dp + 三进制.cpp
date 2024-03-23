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
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 20;
int dp[11][65000];
int maz[15][15];
int p[15];

void init() {
    p[0] = 1;
    for(int i = 1; i < 15; i++) p[i] = p[i-1] * 3;
}

int n, m;
int main() {
    int a, b, c;
    init();
    while(~scanf("%d%d", &n, &m)) {
        for(int i =  0; i < n; i++)
            for(int j = 0; j < n; j++)
                maz[i][j] = inf;
        while(m--) {
            cin >> a >> b >> c;
            a--, b--;
            if(c < maz[a][b]) maz[a][b] = maz[b][a] = c;
        }

        int nn = p[n];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < nn; j++) dp[i][j] = inf;
            dp[i][p[i]] = 0;
        }
        
        for(int j = 0; j < nn; j++) {
            for(int i = 0; i < n; i++) {
                int x = j / p[i] % 3;
                if(x > 0) {
                    for(int k = 0; k < n; k++) {
                        int y = j / p[k] % 3;
                        if(maz[i][k] != inf && y <= 1)  {
                            int nmask = j + p[k];
                            dp[k][nmask] = min(dp[k][nmask], dp[i][j] + maz[i][k]);
                        }
                    }
                }
            }
        }
        int ans = inf;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < nn; j++) {
                bool flag = true;
                for(int k = 0; k < n; k++)
                    if((j / p[k] % 3) == 0) {
                        flag = false;
                        break;
                    }
                if(flag) ans = min(ans, dp[i][j]);
            }
        }

        if(ans != inf) cout << ans << endl;
        else cout << -1 << endl;
    }
    return 0;
}
