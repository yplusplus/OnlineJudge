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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int sum[1<<16], dp[1<<16][16], f[1<<16];
int n, x[16], y[16], c[16], limit;
int dist[16][16], maskSize;

int task1() {
    f[0] = 0;
    for(int mask = 1; mask < maskSize; mask++) {
        f[mask] = inf;
        for(int subMask = mask; subMask; subMask = (subMask - 1) & mask) {
            if(sum[subMask] <= limit) {
                f[mask] = min(f[mask], f[mask ^ subMask] + 1);
            }
        }
    }
    return f[maskSize - 1] == inf ? -1 : f[maskSize - 1];
}

void update(int &x, int a) {
    if(x == -1 || x > a) x = a;
    return;
}

int task2() {
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < n - 1; i++) dp[1 << i][i] = dist[i][n-1];
    f[0] = 0;
    for(int mask = 0; mask < maskSize; mask++) {
        for(int i = 0; i < n - 1; i++) {
            if(dp[mask][i] != -1) {
                for(int j = 0; j < n - 1; j++) {
                    if(~mask >> j & 1) update(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }
    }

    f[0] = 0;
    for(int mask = 1; mask < maskSize; mask++) {
        f[mask] = inf;
        for(int i = 0; i < n - 1; i++) {
            if(sum[mask] <= limit && dp[mask][i] != -1) {
                f[mask] = min(f[mask], dp[mask][i] + dist[i][n-1]);
            }
        }
    }

    for(int mask = 1; mask < maskSize; mask++) {
        for(int subMask = mask; subMask; subMask = (subMask - 1) & mask) {
            f[mask] = min(f[mask], f[mask ^ subMask] + f[subMask]);
        }
    }
    return f[maskSize - 1] == inf ? -1 : f[maskSize - 1];
}

int main() {
    while(~scanf("%d%d", &n, &limit)) {
        for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
        for(int i = 0; i < n; i++) scanf("%d", &c[i]);
        swap(x[0], x[n-1]);
        swap(y[0], y[n-1]);
        swap(c[0], c[n-1]);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = (int)ceil(sqrt(1.0 * (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])));
            }
        }

        maskSize = 1 << (n - 1);
        sum[0] = 0;
        for(int mask = 1; mask < maskSize; mask++) {
            int i = 0;
            while(~mask >> i & 1) i++;
            sum[mask] = sum[mask ^ (1 << i)] + c[i];
        }
        printf("%d %d\n", task1(), task2());
    }
    return 0;
}
