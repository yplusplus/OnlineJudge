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
const int N = 130;
int n;
int tot;
double a[N][N];
double dp[N][N][N];

double dfs(int id, int l, int r) {
    double &tmp = dp[id][l][r];
    if (tmp < 0) {
        tmp = 0;
        int mid = (l + r) >> 1;
        if (id > mid) {
            for (int i = l; i <= mid; i++) {
                tmp += dfs(i, l, mid) * dfs(id, mid + 1, r) * a[id][i];
            }
        } else {
            for (int i = mid + 1; i <= r; i++) {
                tmp += dfs(id, l, mid) * dfs(i, mid + 1, r) * a[id][i];
            }
        }
    }
    return tmp;
}

int main() {
    while (~scanf("%d", &n)) {
        if (n == -1) break;
        tot = 1 << n;
        for (int i = 1; i <= tot; i++) {
            for (int j = 1; j <= tot; j++) {
                scanf("%lf", &a[i][j]);
                for (int k = 1; k <= tot; k++) {
                    dp[i][j][k] = -1;
                }
            }
        }
        for (int i = 1; i <= tot; i++) dp[i][i][i] = 1.0;
        double ansP = -1;
        int ansId = -1;
        for (int i = 1; i <= tot; i++) {
            if (ansP < dfs(i, 1, tot)) {
                ansP = dp[i][1][tot];
                ansId = i;
            }
        }
        cout << ansId << endl;
    }
    return 0;
}

