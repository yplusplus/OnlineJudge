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
const int N = 15555;
int w[N], l[N], pain[N];
bool visit[N];
int n;
pii a[N];
//好题！！！！
//刚开始觉得是贪心，搞了好多天都搞不出来@#￥%￥#@…………&@#￥%
//如果让第N层的水流走，一定是先选择一层p，如果其存水量不大于蓄水量，
//那么手动放水，否则直接流下去。水一层一层流下去，最终可能到达某一层
//能够承受上面很多层流下来的水，这时候这一层一定要手动放水。
//否则，这一层以上的所有操作除了增加了费用之外，对最终结果没有什么影响。
//于是很容易得到一个O(n*n)的算法，枚举最高的放水层，然后模拟放水过程，
//更新费用即可。但是，会TLE，必须要优化！！！！
//试图优化算法：如果选择了第p层放水，在这种情况下，还需要对第q层放水的原因是：
//w[p] + w[p+1] + ... + w[q-1] + w[q] <= l[q];
//从这个式子可以得到一个贪心性质，就是如果选择p1时，q需要手动放水，那么选择
//p2>p1时，q也一定要手动放水。
//有了这一点，我们对每层重新设计一个关键字
//a[i] = w[1] + w[2] + ... + w[i] - l[i];
//如果p为第一层，那么需要手动放水的层一定是a[i] <= 0
//接着p为第二层，那么需要手动放水的层一定是a[i] - w[1] <= 0
//如此类推，可以发现是有单调性的，那么我们一开始只需要按a排序，
//然后就可以用一个不回溯的指针从前往后扫描，找到新的需要放水的层，累加即可。
//这样时间复杂度为O(nlogn)。

int main() {
    while (cin >> n) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> w[i] >> l[i] >> pain[i];
            sum += w[i];
            a[i] = mp(sum - l[i], i);
        }
        sort(a + 1, a + 1 + n);
        memset(visit, false, sizeof(visit));
        int p = 1;
        int delta = 0;
        int ansPain = inf, ansId = -1, tmpPain = 0;
        for (int i = 1; i <= n; i++) {
            while (p <= n && a[p].fi - delta <= 0) {
                visit[a[p].se] = true;
                tmpPain += pain[a[p].se];
                p++;
            }
            if (visit[i-1]) tmpPain -= pain[i-1];
            if (tmpPain < ansPain) {
                ansPain = tmpPain;
                ansId = i;
            }
            delta += w[i];
        }
        for (int i = ansId, tmpW = 0; i <= n; i++) {
            tmpW += w[i];
            if (tmpW <= l[i]) cout << i << endl;
        }
    }
    return 0;
}
