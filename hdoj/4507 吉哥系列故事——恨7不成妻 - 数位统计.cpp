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
const ll MOD = 1000000007LL;
const int bitnum = 20;
ll cnt[bitnum][10][10];
ll s[bitnum][10][10];
ll sq[bitnum][10][10];
ll fac[bitnum];
int digit[bitnum];

ll add(ll a, ll b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

ll mul(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < bitnum; i++) {
        fac[i] = fac[i-1] * 10;
    }
    memset(cnt, 0, sizeof(cnt));
    memset(s, 0, sizeof(s));
    memset(sq, 0, sizeof(sq));
    for (int d = 0; d <= 9; d++) {
        if (d == 7) continue;
        cnt[0][d % 7][d % 7]++;
        s[0][d % 7][d % 7] += d;
        sq[0][d % 7][d % 7] += d * d;
    }
    for (int i = 0; i < bitnum - 1; i++) {
        for (int d = 0; d <= 9; d++) {
            if (d == 7) continue;
            for (int sum = 0; sum < 7; sum++) {
                for (int r = 0; r < 7; r++) {
                    int newSum = (sum + d) % 7;
                    int newR = (d * (fac[i+1] % 7) + r) % 7;
                    ll head = mul(d, fac[i+1]);
                    cnt[i+1][newSum][newR] = add(cnt[i+1][newSum][newR], cnt[i][sum][r]);
                    s[i+1][newSum][newR] = add(add(s[i+1][newSum][newR], s[i][sum][r]), mul(cnt[i][sum][r], head));
                    sq[i+1][newSum][newR] = add(sq[i+1][newSum][newR], mul(mul(head, head), cnt[i][sum][r]));
                    sq[i+1][newSum][newR] = add(sq[i+1][newSum][newR], sq[i][sum][r]);
                    sq[i+1][newSum][newR] = add(sq[i+1][newSum][newR], mul(mul(head, s[i][sum][r]), 2));
                }
            }
        }
    }
}

ll dfs(int i, ll head, ll sum, ll r, bool e) {
    if (i == -1) {
        return (sum && r) ? mul(head, head) : 0;
    }
    ll res = 0;
    if (!e) {
        for (int _sum = 0; _sum < 7; _sum++) {
            for (int _r = 0; _r < 7; _r++) {
                int newSum = (sum + _sum) % 7;
                int newR = (r * (fac[i+1] % 7) + _r) % 7;
                if (newSum && newR) {
                    res = add(res, mul(mul(head, head), cnt[i][_sum][_r]));
                    res = add(res, sq[i][_sum][_r]);
                    res = add(res, mul(mul(head, s[i][_sum][_r]), 2));
                }
            }
        }
        return res;
    } else {
        for (int d = 0; d <= digit[i]; d++) {
            if (d == 7) continue;
            res = add(res, dfs(i - 1, add(head, mul(d, fac[i])), (sum + d) % 7, (r * 10 + d) % 7, e && d == digit[i]));
        }
        return res;
    }
}

ll calc(ll x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 0, 0, 1);
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        ll l, r;
        cin >> l >> r;
        cout << ((((calc(r) - calc(l - 1)) % MOD) + MOD) % MOD) << endl;
    }
    return 0;
}
