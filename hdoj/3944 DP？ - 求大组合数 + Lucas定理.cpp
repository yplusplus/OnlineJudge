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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxp 10050
ll n, k, p;
ll fac[maxp][1500];
int prime[maxp], hash[maxp];
bool visit[maxp];

void init() {
    memset(visit, false, sizeof(visit));
    int tot = 0;
    prime[tot] = 2, hash[2] = tot, tot++;
    for(int i = 3; i < maxp; i += 2) {
        if(!visit[i]) {
            prime[tot] = i, hash[i] = tot, tot++;
            if(i * i < maxp)
                for(int j = 2 * i; j < maxp; j += i) visit[j] = true;
        }
    }
    for(int i = 0; i < tot; i++) {
        fac[0][i] = 1;
        for(int j = 1; j < maxp; j++) {
            fac[j][i] = (fac[j-1][i] * j) % prime[i];
        }
    }
}

ll quickpower(ll x, ll n) {
    ll res = 1;
    x %= p;
    while(n) {
        if(n & 1) res = res * x % p;
        x = x * x % p;
        n >>= 1;
    }
    return res;
}

ll C(ll n, ll k, ll p) {
    ll res = 1;
    if(k > n) return 0;
    res = fac[n][hash[p]] * quickpower(fac[n-k][hash[p]] * fac[k][hash[p]], p - 2) % p;
    return res;
}

ll Lucas(ll n, ll k, ll p) {
    if(k == 0) return 1;
    return C(n % p, k % p, p) * Lucas(n / p, k / p, p) % p;
}

int main() {
    int Case = 1;
    init();
    while(~scanf("%lld%lld%lld", &n, &k, &p)) {
        if(k > n / 2) k = n - k;
        ll ans = (Lucas(n+1, k, p) + n - k) % p;
        printf("Case #%d: %lld\n", Case++, ans);
    }
    return 0;
}
