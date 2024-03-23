#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 210
int n, val[maxn], cnt;
int f[maxn][maxn][maxn];
int len[maxn], color[maxn];

int calc(int x) {
    return x * x;
}

int dp(int l, int r, int k) {
    if(f[l][r][k]) return f[l][r][k];
    if(l == r) return f[l][r][k] = calc(k + len[r]);
    f[l][r][k] = dp(l, r - 1, 0) + calc(len[r] + k);
    for(int i = l; i < r; i++) 
        if(color[i] == color[r])
            f[l][r][k] = max(f[l][r][k], dp(l, i, k + len[r]) + dp(i + 1, r - 1, 0));
    return f[l][r][k];
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &val[i]);
        color[0] = -1, cnt = 0;
        for(int i = 0; i < n; i++) {
            if(val[i] == color[cnt]) len[cnt]++;
            else color[++cnt] = val[i], len[cnt] = 1;
        }
        memset(f, 0, sizeof(f));
        int ans = dp(1, cnt, 0);
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
