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
const ll MOD = 55566677LL;
const int N = 55;
const int M = 30;
ll fac[N];
bool day[N], chap[N];
pii con[M];
int tot;
int n, m;
ll dfs(int i, int cnt) {
    if (i == tot) {
        if (cnt & 1) return MOD - fac[n - cnt];
        else return fac[n - cnt];
    }
    ll res = dfs(i + 1, cnt);
    if (!day[con[i].fi] && !chap[con[i].se]) {
        day[con[i].fi] = chap[con[i].se] = true;
        res = (res + dfs(i + 1, cnt + 1)) % MOD;
        day[con[i].fi] = chap[con[i].se] = false;
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    while (cin >> n >> m) {
        for (int i = 0; i < m; i++) {
            cin >> con[i].fi >> con[i].se;
        }
        sort(con, con + m);
        tot = unique(con, con + m) - con;
        memset(day, false, sizeof(day));
        memset(chap, false, sizeof(chap));
        cout << dfs(0, 0) << endl;
    }
    return 0;
}
