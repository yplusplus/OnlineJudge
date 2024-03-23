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
const int inf = 1 << 30;
const int N = 111;
int dp[N][N];
int sum[N];
int n;

int dfs(int l, int r) {
    if (l > r) return 0;
    //if (l == r) return sum[l] - sum[l - 1];
    int len = r - l + 1;
    if (dp[l][r] != -1) return dp[l][r];
    int res = inf;
    for (int i = 1; i <= len; i++) {
        res = min(res, (i - 1) * (sum[l] - sum[l - 1]) + dfs(l + 1, l + i - 1) + dfs(l + i, r) + i * (sum[r] - sum[l + i - 1]));
    }
    //cout << l << " " << r << " " << res << endl;
    return dp[l][r] = res;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
    sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &sum[i]);
            sum[i] += sum[i - 1];
        }
        memset(dp, -1, sizeof(dp));
        printf("Case #%d: %d\n", Case++, dfs(1, n));
    }
    return 0;
}

