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
const int inf = 1 << 30;
#define maxn 1050
int sum[maxn], n;
int main() {
    int T, Case = 1;
    cin >> T;
    sum[0] = 0;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> sum[i];
            sum[i] += sum[i-1];
        }
        int ans = inf;
        for(int i = 1; i <= n; i++) {
            for(int j = i; j <= n; j++) {
                ans = min(ans, abs(sum[j] - sum[i-1]));
            }
        }
        printf("Case %d: ", Case++);
        cout << ans << endl;
    }
    return 0;
}
