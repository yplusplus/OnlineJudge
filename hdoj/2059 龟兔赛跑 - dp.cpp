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

int n;
double l, vr, v1, v2, c, t;
double dp[110], p[110];
int main() {
    while(~scanf("%lf", &l)) {
        scanf("%d%lf%lf", &n, &c, &t);
        scanf("%lf%lf%lf", &vr, &v1, &v2);
        for(int i = 1; i <= n; i++) scanf("%lf", &p[i]);
        p[0] = 0, p[n+1] = l;
        dp[0] = -t;
        for(int i = 1; i <= n + 1; i++) {
            dp[i] = 1e30;
            for(int j = 0; j < i; j++) {
                double tmp = t;
                double dist = p[i] - p[j];
                if(dist > c) tmp += c / v1 + (dist - c) / v2;
                else tmp += dist / v1;
                dp[i] = min(dp[i], dp[j] + tmp);
            }
        }
        if(dp[n+1] > l / vr) puts("Good job,rabbit!");
        else puts("What a pity rabbit!");
    }
    return 0;
}
