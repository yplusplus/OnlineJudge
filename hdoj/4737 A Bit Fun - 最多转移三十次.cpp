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

const int N = 111111;
int pos[N][32];
int n, m;
int a[N];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for (int j = 0; j <= 30; j++) pos[n + 1][j] = n + 1;
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j <= 30; j++) {
                if (a[i] >> j & 1) pos[i][j] = i;
                else pos[i][j] = pos[i + 1][j];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int t = a[i];
            int position = i;
            while (t < m && position <= n) {
                int mi = n + 1;
                int tmp = 0;
                for (int j = 0; j <= 30; j++) {
                    if (~t >> j & 1) {
                        if (pos[position + 1][j] < mi) {
                            mi = pos[position + 1][j];
                            tmp = 0;
                        }
                        if (pos[position + 1][j] == mi) {
                            tmp |= 1 << j;
                        }
                    }
                }
                if (position == n + 1) break;
                t |= tmp;
                position = mi;
                //cout << tmp << " " << mi << endl;
            }
            //cout << i << " " << position << " " << t << endl;
            ans += position - i;
        } 
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
