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

//不错的题目，因为2^23 > 500000，所以答案最长是23
//怕23 * 2^23 会TLE，所以加了二分
//复杂度O(nloglogn)
string str;
int n, ans, ansMask;
bool visit[1<<23];
int calc(int mid) {
    int mask = 0;
    int all = 1 << mid;
    int cnt = 0;
    memset(visit, false, sizeof(bool) * all);
    for(int i = 0; i < mid; i++) {
        if(str[i]) mask |= (1 << i);
    }
    visit[mask] = true;
    cnt++;
    for(int i = mid; i < n; i++) {
        mask >>= 1;
        if(str[i]) mask |= (1 << (mid - 1));
        if(!visit[mask]) {
            visit[mask] = true;
            if(++cnt == all) return -1;
        }
    }
    for(int i = 0; i < all; i++) {
        if(!visit[i]) return i;
    }
}

void solve() {
    int l = 1, r = min(n, 23);
    while(l <= r) {
        int mid = (l + r) >> 1;
        int tmp = calc(mid);
        if(tmp != -1) {
            ansMask = tmp;
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return;
}

int main() {
    while(cin >> n) {
        cin >> str;
        for(int i = 0; i < str.length(); i++) str[i] -= 'a';
        solve();
        cout << ans << endl;
        for(int i = 0; i < ans; i++) {
            putchar((ansMask >> i & 1) ? 'b' : 'a');
        }
        puts("");
    }
    return 0;
}
