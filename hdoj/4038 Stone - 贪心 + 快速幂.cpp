#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;
#define ll long long
#define maxn 105000
#define MOD 1000000007
int n, minn, maxx, index;
int po[maxn], pcnt, ne[maxn], ncnt;
ll num[5], m;

void init() {
	memset(num, 0, sizeof(num));
	pcnt = ncnt = 0;
	minn = 1 << 30;
	index = -1;
}

ll quickpow(ll x, ll n)
{
	ll res = 1;
    while (n) {
        if(n & 1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}

ll solve() {
	ll res = 1;
	sort(ne, ne + ncnt);
	if(ncnt % 2) {
		if(m + ne[ncnt-1] >= 0) ncnt--, m += ne[ncnt], num[0]++;
		else ne[ncnt-1] += m, m = 0;
	}
	if(m >= num[0]) num[1] += num[0], m -= num[0], num[0] = 0;
	else return 0;
	if(m >= num[1]) num[2] += num[1], m -= num[1], num[1] = 0;
	else num[1] -= m, num[2] += m, m = 0;
	if(m >= num[2]) num[3] += num[2], m -= num[2], num[2] = 0;
	else num[2] -= m, num[3] += m, m = 0;
	num[3] += m / 3, m %= 3;
	if(m == 2) num[2]++;
	else if(m == 1 && num[3]) num[3]--, num[2] += 2;
	else if(m == 1 && index !=- 1) po[index]++;
	for(int i = 0; i < ncnt; i++) res *= ne[i], res %= MOD;
	for(int i = 0; i < pcnt; i++) res *= po[i], res %= MOD;
	res = res * quickpow(2, num[2]) % MOD;
	res = res * quickpow(3, num[3]) % MOD;
	return res;
}

int main() {
	int T, a;
	scanf("%d", &T);
	for(int tt = 1; tt <= T; tt++) {
		scanf("%d%lld", &n, &m);
		init();
		for(int i = 0; i < n; i++) {
			scanf("%d", &a);
			if(a < 0) ne[ncnt++] = a;
			else if(a > 3) {
				if(a < minn) minn = a, index = pcnt;
				po[pcnt++] = a;
			}
			else num[a]++;
		}
		ll ans = solve();
		printf("Case %d: %lld\n", tt, ans);
	}
	return 0;
}