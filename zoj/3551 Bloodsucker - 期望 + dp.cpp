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
#define maxn 100050
double dp[maxn], p;
int n;
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d%lf", &n, &p);
        dp[n] = 0.0;
        for(int i = n - 1; i; i--) {
            double pp = 2.0 * i * (n - i) * p / n / (n - 1);
            dp[i] = dp[i+1] + 1.0 / pp;
        }
        printf("%.3f\n", dp[1]);
    }
    return 0;
}
