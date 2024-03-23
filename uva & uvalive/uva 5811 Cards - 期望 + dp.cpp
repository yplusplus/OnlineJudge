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
int aa, bb, cc, dd;
double dp[16][16][16][16][5][5];
bool visit[16][16][16][16][5][5];

double dfs(int a, int b, int c, int d, int big, int small) {
    double &tmp = dp[a][b][c][d][big][small];
    if(visit[a][b][c][d][big][small]) return tmp;
    visit[a][b][c][d][big][small] = true;
    int now[] = {a, b, c, d};
    if(big != 4) now[big]++;
    if(small != 4) now[small]++;
    if(now[0] >= aa && now[1] >= bb && now[2] >= cc && now[3] >= dd) return tmp = 0.0;
    tmp = 1.0;
    double sum = now[0] + now[1] + now[2] + now[3];
    if(a < 13) tmp += dfs(a + 1, b, c, d, big, small) * (13.0 - a) / (54.0 - sum);
    if(b < 13) tmp += dfs(a, b + 1, c, d, big, small) * (13.0 - b) / (54.0 - sum);
    if(c < 13) tmp += dfs(a, b, c + 1, d, big, small) * (13.0 - c) / (54.0 - sum);
    if(d < 13) tmp += dfs(a, b, c, d + 1, big, small) * (13.0 - d) / (54.0 - sum);
    if(big == 4) {
        double tmp1 = 1e100;
        tmp1 = min(tmp1, dfs(a, b, c, d, 0, small) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, 1, small) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, 2, small) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, 3, small) / (54.0 - sum));
        tmp += tmp1;
    }
    if(small == 4) {
        double tmp1 = 1e100;
        tmp1 = min(tmp1, dfs(a, b, c, d, big, 0) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, big, 1) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, big, 2) / (54.0 - sum));
        tmp1 = min(tmp1, dfs(a, b, c, d, big, 3) / (54.0 - sum));
        tmp += tmp1;
    }
    return tmp;
}

int main() {
    int T, Case = 1;
    cin >> T;
    while(T--) {
        cin >> aa >> bb >> cc >> dd;
        int cnt = 0;
        cnt += max(aa - 13, 0);
        cnt += max(bb - 13, 0);
        cnt += max(cc - 13, 0);
        cnt += max(dd - 13, 0);
        printf("Case %d: ", Case++);
        if(cnt > 2) printf("-1.000\n");
        else {
            memset(visit, false, sizeof(visit));
            printf("%.3f\n", dfs(0, 0, 0, 0, 4, 4));
        }
    }
    return 0;
}
