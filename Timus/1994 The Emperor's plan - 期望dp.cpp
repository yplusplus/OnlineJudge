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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 222;
const int M = 22;

bool visit[N][M];
double dp[N][M];
double c[N][N];

void init() {
    for (int i = 0; i < N; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
}

double dfs(int n, int m) {
    if (m == 0) return n;
    if (n <= 2 * m) return 0;
    if (visit[n][m]) return dp[n][m];
    visit[n][m] = 1;
    double ret = 0;
    int r = n - m;
    for (int i = 0; i <= r; i++) {
        double sum = 0;
        for (int j = 0; j <= i && j <= m; j++) {
            sum += dfs(r - i, m - j) * c[m][j] / c[n - m][i] * c[r - m][i - j];
        }
        ret = max(ret, sum);
    }
    return dp[n][m] = ret;
}

int main() {
    init();
    memset(visit, 0, sizeof(visit));
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        printf("%.20f\n", dfs(n, m));
    }
    return 0;
}
