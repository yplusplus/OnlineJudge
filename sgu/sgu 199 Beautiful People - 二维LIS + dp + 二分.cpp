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
int n;
int rec[N], pre[N];
//优先按s从小到大排序，其次按b从大到小排序
//这样就把二维LIS转化成一维，N达到10^5，利用二分，O(nlogn)
//rec[i] 记录长度为i的上升子序列最后一个值最小的时候，下标为rec[i]
struct Person {
    int s, b, id;
    Person(){}
    Person(int _s, int _b, int _id) {
        s = _s, b = _b, id = _id;
    }
    bool operator< (const Person &x) const {
        if(s != x.s) return s < x.s;
        else return b > x.b;
    }
}p[N];

int bs(int a, int x) {
    int l = 0, r = a;
    int res;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(p[rec[mid]].b < x) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    while(cin >> n) {
        for(int i = 1, a, b; i <= n; i++) {
            cin >> a >> b;
            p[i] = Person(a, b, i);
        }
        sort(p + 1, p + 1 + n);
        p[0] = Person(0, 0, 0);
        rec[0] = 0;
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            int res = bs(ans, p[i].b);
            if(res == ans) ans++;
            rec[res + 1] = i;
            pre[i] = rec[res];
        }
        cout << ans << endl;
        int x = rec[ans];
        while(x) {
            cout << p[x].id << endl;
            x = pre[x];
        }
    }
    return 0;
}
