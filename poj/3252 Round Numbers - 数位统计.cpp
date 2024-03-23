#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int OFFSET = 32;
int dp[32][64][2];
int digit[32];
int tot;

int dfs(int pos, int delta, bool e, bool o) {
    if (pos == -1) {
        return o && delta >= OFFSET;
    }
    if (!e && dp[pos][delta][o] != -1) return dp[pos][delta][o];
    int u = e ? digit[pos] : 1;
    int res = 0;
    for (int d = 0; d <= u; d++) {
        int ndelta = delta;
        bool ne = (e && u == d);
        bool no = (o || d == 1);
        if (no) 
            ndelta = delta + (d == 0 ? 1 : -1);
        res += dfs(pos - 1, ndelta, ne, no);
    }
    return e ? res : dp[pos][delta][o] = res;
}

int calc(int x) {
    if (x == 0) return 0;
    tot = 0;
    while (x) {
        digit[tot++] = x & 1;
        x >>= 1;
    }
    return dfs(tot - 1, OFFSET, true, false);
}

int main() {
    int L, R;
    memset(dp, -1, sizeof(dp));
    while (cin >> L >> R) {
        cout << calc(R) - calc(L - 1) << endl;
    }
    return 0;
}


