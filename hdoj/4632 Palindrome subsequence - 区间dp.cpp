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

const int MOD = 10007;
const int N = 1111;
int dp[N][N];
char str[N];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str);
        int n = strlen(str);
        memset(dp, 0, sizeof(0));
        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
                if (str[i] == str[j]) dp[i][j] = (dp[i][j] + dp[i + 1][j - 1] + 1) % MOD;
            }
        }
        printf("Case %d: %d\n", Case++, dp[0][n - 1]);
    }
    return 0;
}

