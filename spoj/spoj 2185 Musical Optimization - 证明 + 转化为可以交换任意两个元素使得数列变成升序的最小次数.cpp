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
int sum[N];
bool visit[N];
int n;
int main() {
    while (~scanf("%d", &n)) {
        sum[0] = 0;
        bool found = false;
        vector<int> vec;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &sum[i]);
            sum[i] += sum[i - 1];
            vec.pb(sum[i]);
            found |= (sum[i] <= 0);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        found |= vec.size() < n;
        if (found) {
            puts("-1");
            continue;
        }
        for (int i = 1; i <= n; i++) {
            visit[i] = false;
            sum[i] = lower_bound(vec.begin(), vec.end(), sum[i]) - vec.begin() + 1;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!visit[i]) {
                int x = i, cnt = 0;
                while (!visit[x]) {
                    cnt++;
                    visit[x] = true;
                    x = sum[x];
                }
                ans += cnt - 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
