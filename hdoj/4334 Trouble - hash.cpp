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
const ll delta = 10000000000000000LL;
int n;
const ll MOD = 104729;
bool bhash[MOD];
ll vhash[MOD], val[5][210];
int cnt[MOD];
bool find_hash(ll &pos) {
    ll val = pos;
    pos %= MOD;
    while(bhash[pos]) {
        if(vhash[pos] == val) return true;
        pos++;
        if(pos >= MOD) pos -= MOD;
    }
    return false;
}

ll make_hash(ll val) {
    ll pos = val;
    if(!find_hash(pos)) {
        bhash[pos] = true;
        vhash[pos] = val;
        cnt[pos] = 0;
    }
    ++cnt[pos];
    return pos;
}

bool solve() {
    memset(bhash, false, sizeof(bhash));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll tmp = delta + val[0][i] + val[1][j];
            make_hash(tmp);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                ll tmp = -(val[2][i] + val[3][j] + val[4][k]) + delta;
                if(find_hash(tmp)) return true;
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < n; j++)
                scanf("%I64d", &val[i][j]);
        if(solve()) puts("Yes");
        else puts("No");
    }
    return 0;
}
