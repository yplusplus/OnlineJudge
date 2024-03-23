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
#define maxn 25
ll dp[maxn];

ll id(int n, char c, char *s) {
    if(*s == 0) return 0;
    ll tmp = 1;
    for(char i = '0'; i < *s; i++) {
        if(i == c) continue;
        tmp += dp[n-1];
    }
    tmp += id(n - 1, *s, s + 1);
    return tmp;
}

void dfs(int n, ll k, char c, char *s) {
    if(k == 0) {
        *s = '\0';
    } else {
        k--;
        for(*s = '0'; ; (*s)++) {//++*s
            if(*s == c) continue;
            if(k < dp[n-1]) {
                dfs(n - 1, k, *s, s + 1);
                break;
            } else k -= dp[n-1];
        }
    }
}

int main() {
    int n;
    ll k;
    char s[maxn];
    dp[0] = 1;
    for(int i = 1; i < maxn; i++) dp[i] = dp[i-1] * 3;
    for(int i = 1; i < maxn; i++) dp[i] += dp[i-1];
    while(~scanf("%d%lld%s", &n, &k, s)) {
        k = id(n, '0', s) - k;
        dfs(n, k, '0', s);
        puts(s);
    }
    return 0;
}
