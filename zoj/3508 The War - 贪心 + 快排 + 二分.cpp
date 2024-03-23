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
#include "set"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 40010
#define maxn 3000
typedef pair<int, int> pii;
int n, m;
pii p[maxn];
bool cmp(const pii &a, const pii &b) {
    return a.se < b.se;
}

int main() {
    multiset<int> s;
    multiset<int>::iterator it;
    while(cin >> n >> m) {
        s.clear();
        for(int i = 0; i < n; i++) cin >> p[i].fi >> p[i].se;
        for(int i = 0, a; i < m; i++) {
            cin >> a;
            s.insert(a);
        }
        sort(p, p + n, cmp);
        int ans = 0;
        for(int i = 0; i < n; i++) {
            it = s.lower_bound(p[i].fi);
            if(it != s.end() && *it <= p[i].se) {
                ans++;
                s.erase(it);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
