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
const int N = 66666;
int sum[N], a[N];
int n;
vector<int> vec;

int bs(int x) {
    int l = 0, r = vec.size() - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(vec[mid] == x) return mid + 1;
        else if(vec[mid] > x) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

void update(int x, int v) {
    for(int i = x; i < N; i += lowbit(i)) sum[i] += v;
}

int query(int x) {
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) {
        res += sum[i];
    }
    return res;
}

int main() {
    while(cin >> n) {
        memset(sum, 0, sizeof(sum));
        vec.clear();
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            vec.pb(a[i]);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int idx = bs(a[i]);
            ans += query(vec.size()) - query(idx);
            update(idx, 1);
        }
        cout << ans << endl;
    }
    return 0;
}
