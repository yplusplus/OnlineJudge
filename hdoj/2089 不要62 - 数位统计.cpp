#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
int dp[15][10];
int digit[15];

int dfs(int i, int pre, bool e) {
    if (i == -1) return 1;
    if (!e && ~dp[i][pre]) return dp[i][pre];
    int u = e ? digit[i] : 9;
    int res = 0;
    for (int d = 0; d <= u; d++) {
        if (d == 4 || (d == 2 && pre == 6)) continue;
        res += dfs(i - 1, d, e & d == u);
    }
    return e ? res : dp[i][pre] = res;
}

int calc(int x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, true);
}

int main() {
    int l, r;
    memset(dp, -1, sizeof(dp));
    while (cin >> l >> r, l + r) {
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}

