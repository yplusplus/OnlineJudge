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
const int M = 1000000;
const int N = 111111;
int a[N], cnt[M + 10];
int n;
int main() {
    while(~scanf("%d", &n)) {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < n; i++) {
            int tmp = (int)ceil(sqrt(double(a[i])));
            //cout << tmp << endl;
            for(int j = 1; j <= tmp; j++) {
                if(a[i] % j == 0) {
                    cnt[j]++;
                    if(a[i] / j != j) cnt[a[i] / j]++;
                    //cout << j << " " << a[i] / j << endl;
                }
            }
        }
        int ans = 1;
        for(int i = M; i > 0; i--) {
            if(cnt[i] > 1) {
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
