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

double dp[4010][4];
double p[4010][4];
int n, a, b;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &a, &b);
        memset(p, 0, sizeof(p));
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++)
            scanf("%lf%lf%lf%lf", &p[i][0], &p[i][1], &p[i][2], &p[i][3]);
        for(int i = n + 1; i <= n + a; i++) p[i][3] = 1.0;
        double c = 1.0;
        for(int i = n; i >= 0; i--) {
            for(int j = 1; j < 4; j++) {
                double pp = 1.0;
                for(int k = a; k <= b; k++) {
                    if(j == 1) {
                        dp[i][1] += pp * ((dp[i+k][2] + c) * p[i+k][2] + (dp[i+k][3] + c) * p[i+k][3]);
                        pp *= (p[i+k][0] + p[i+k][1]);
                    } else if(j == 2) {
                        dp[i][2] += pp * ((dp[i+k][1] + c) * p[i+k][1] + (dp[i+k][3] + c) * p[i+k][3]);
                        pp *= (p[i+k][0] + p[i+k][2]);
                    } else if(j == 3) {
                        dp[i][3] += pp * ((dp[i+k][1] + c) * p[i+k][1] + (dp[i+k][2] + c) * p[i+k][2] + (dp[i+k][3] + c) * p[i+k][3]);
                        pp *= (p[i+k][0]);
                    }
                }
            }
        }
        printf("%.6f\n", dp[0][3]);
    }
    return 0;
}
