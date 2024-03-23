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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 1050
map<int, double> prob;
int n, m, tot;
int pos[maxn];
double w[maxn], sumw[maxn], sum[maxn];
double dp[55][maxn];
double cost[maxn][maxn];
int main() {
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        prob.clear();
        tot = 0;
        for(int i = 0; i < n; i++) {
            int x, cnt;
            double p;
            scanf("%d", &cnt);
            while(cnt--) {
                scanf("%d%lf", &x, &p);
                prob[x] += p;
            }
        }
        sum[0] = sumw[0] = 0;
        for(map<int, double>::iterator it = prob.begin(); it != prob.end(); it++) {
            pos[++tot] = it->fi;
            w[tot] = it->se;
        }

        for(int i = 1; i <= tot; i++) {
            sumw[i] = sumw[i-1] + w[i];
            sum[i] = sum[i-1] + pos[i] * w[i];
        }

        for(int i = 1; i <= tot; i++) {
            int idx = i;
            for(int j = i; j <= tot; j++) {
                cost[i][j] = 0.0;
                while(idx + 1 <= j && sumw[idx] * 2.0 < sumw[j] + sumw[i-1]) idx++;
                cost[i][j] += (sumw[idx-1] - sumw[i-1]) * pos[idx] - (sum[idx-1] - sum[i-1]);
                cost[i][j] += (sum[j] - sum[idx]) - (sumw[j] - sumw[idx]) * pos[idx];
                //cout << cost[i][j] << " ";
            }
            //cout << endl;
        }

        for(int i = 0; i <= m; i++)
            for(int j = 0; j <= tot; j++)
                dp[i][j] = dinf;

        dp[0][0] = 0.0;

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= tot; j++) {
                for(int k = 0; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + cost[k+1][j]);
                }
                //cout << dp[i][j] << " ";
            }
            //cout << endl;
        }
        printf("%.2f\n", dp[m][tot]);
    }
    return 0;
}
