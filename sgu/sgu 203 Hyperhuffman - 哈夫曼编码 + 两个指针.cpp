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
const int N = 555555;
int n;
ll a[N<<1];
//哈夫曼编码，一直用O(nlogn)的复杂度写，狂TLE
//查了下论文，原来在有序情况下可以O(n)构造, 只需要维护两个指针即可
//用cin会TLE，scanf才能过

ll get(int &p1, int &p2, int i) {
    ll rec = -linf;
    if(p1 <= n && p2 < n + i) {
        if(a[p1] <= a[p2]) {
            rec = a[p1++];
        } else {
            rec = a[p2++];
        }
    } else if(p1 > n) {
        rec = a[p2++];
    } else {
        rec = a[p1++];
    }
    return rec;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%I64d", &a[i]);
    }
    ll ans = 0;
    int p1 = 1, p2 = n + 1;
    for(int i = 1; i < n; i++) {
        a[n + i] = 0;
        a[n + i] += get(p1, p2, i);
        a[n + i] += get(p1, p2, i);
        ans += a[n + i];
    }
    printf("%I64d\n", ans);
    return 0;
}
