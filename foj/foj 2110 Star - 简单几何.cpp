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
const int N = 111;
pair<ll, ll> p[N];
int n;
ll getdist(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se);
}

bool check(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
    ll line[3];
    line[0] = getdist(a, b);
    line[1] = getdist(a, c);
    line[2] = getdist(b, c);
    sort(line, line + 3);
    return line[0] + line[1] > line[2];
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            cin >> p[i].fi >> p[i].se;
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                for(int k = j + 1; k < n; k++) {
                    if(check(p[i], p[j], p[k])) ans++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
