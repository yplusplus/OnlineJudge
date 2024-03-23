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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const ll mod = 1000000007LL;
#define MAX 110
#define maxn 1000050
int n, pn;
bool ispri[maxn];
ll C[MAX][MAX];
int pri[80000], cnt[80000];
void init() {
    for(int i = 0; i < MAX; i++) { 
        C[i][i] = C[i][0] = 1;
        for(int j = 1; j < i; j++) 
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }
    memset(ispri, true, sizeof(ispri));
    pn = 0;
    for(ll i = 2; i < maxn; i++) {
        if(ispri[i]) {
            pri[pn++] = i;
            for(ll j = i * i; j < maxn; j += i) ispri[j] = false;
        }
    }
}

ll calc(ll n, ll m) {
    return C[n+m-1][m-1];
}
int main() {
    init();
    while(~scanf("%d", &n)) {
        vector<int> vec, vv;
        vec.clear();
        vv.clear();
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            for(int j = 0; j < pn && a != 1; j++) {
                if(a % pri[j] == 0) {
                    vec.pb(j);
                    while(a % pri[j] == 0) {
                        cnt[j]++;
                        a /= pri[j];
                    }
                }
            }
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        for(int i = 0; i < vec.size(); i++) {
            vv.pb(cnt[vec[i]]);
        }
        ll ans = 0;
        for(int i = 0; i <= n; i++) {
            ll res = C[n][i];
            for(int j = 0; j < vv.size(); j++) {
                res = (res * calc(vv[j], n - i)) % mod;
            }
            if(i & 1) ans = (ans - res + mod) % mod;
            else ans = (ans + res) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
