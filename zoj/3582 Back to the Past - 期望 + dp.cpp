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
#define maxn 110
double dp[55][55];
double p1[maxn], p2[maxn];
double C[55][55];
int n, m;
double p;
bool visit[55][55];
void init() {
    for(int i = 0; i < 51; i++) C[i][0] = C[i][i] = 1;
    for(int i = 2; i < 51; i++)
        for(int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
}

double dfs(int a, int b) {
    double &tmp = dp[a][b];
    if(visit[a][b]) return tmp;
    visit[a][b] = true;
    if(a >= m && b >= m) return tmp = 0.0;
    tmp = 1.0;
    for(int i = 0; i <= n - a; i++) {
        for(int j = 0; j <= n - b; j++) {
            if(i == 0 && j == 0) continue;
            tmp += (dfs(a + i, b + j)) * p1[i+j] * p2[2 * n - a - b - i - j] * C[n-a][i] * C[n-b][j];
        }
    }
    return tmp /= (1 - p2[2 * n - a - b]);
}

int main() {
    init();
    while(~scanf("%d%d%lf", &n, &m, &p)) {
        if(!n && !m) break;
        p1[0] = p2[0] = 1.0;
        for(int i = 1; i < maxn; i++) p1[i] = p1[i-1] * p;
        for(int i = 1; i < maxn; i++) p2[i] = p2[i-1] * (1 - p);
        memset(visit, false, sizeof(visit));
        printf("%.6f\n", dfs(0, 0));
    }
    return 0;
}
