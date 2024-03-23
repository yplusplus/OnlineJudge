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
const int N = 100001;
vector<int> vec[N];
int prime[N], tot;
bool isPrime[N];
int n, m;

void init() {
    memset(isPrime, true, sizeof(isPrime));
    tot = 0;
    for (ll i = 2; i < N; i++) {
        if (isPrime[i]) {
            prime[tot++] = i;
            for (ll j = i * i; j < N; j += i) isPrime[j] = false;
        }
    }
    for (int i = 1; i < N; i++) {
        int x = i;
        for (int j = 0; j < tot && x != 1; j++) {
            if (x % prime[j] == 0) {
                vec[i].pb(prime[j]);
                while (x % prime[j] == 0) x /= prime[j];
            }
        }
    }
}

int dfs(int s, int x, int cnt, int prod) {
    if (s == vec[x].size()) {
        return (n / prod) * ((~cnt & 1) ? 1 : -1);
    } else {
        return dfs(s + 1, x, cnt, prod) + dfs(s + 1, x, cnt + 1, prod * vec[x][s]);
    }
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (n < m) swap(n, m);
        ll ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += dfs(0, i, 0, 1);
        }
        cout << ans << endl;
    }
    return 0;
}
