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
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 110
#define maxl 1000050
char s[maxn];
int l, cnt;
int prime[100000], pn;
ll val[maxn];

void getprime() {
    bool isprime[maxl];
    memset(isprime, true, sizeof(isprime));
    pn = 0;
    for(ll i = 2; i < maxl; i++) {
        if(isprime[i]) {
            prime[pn++] = i;
            for(ll j = i * i; j < maxl; j += i) isprime[j] = false;
        }
    }
}

void work() {
    int len = strlen(s);
    ll res = 0;
    cnt = 0;
    for(int i = 0; i < len % 10; i++) {
        res *= 10;
        res += s[i] - '0';
    }
    val[cnt++] = res;
    for(int i = len % 10; i < len; i += 10) {
        res = 0;
        for(int j = i; j < i + 10; j++) {
            res *= 10;
            res += s[j] - '0';
        }
        val[cnt++] = res;
    }
}

int main() {
    getprime();
    while(~scanf("%s%d", s, &l)) {
        if(s[0] == '0' && l == 0) break;
        work();
        bool flag = true;
        int len = (strlen(s) + 9) / 10;
        for(int i = 0; i < pn && prime[i] < l; i++) {
            ll res = 0;
            for(int j = 0; j < cnt; j++) {
                res = res * 10000000000LL + val[j];
                res %= prime[i];
            }
            if(res == 0) {
                printf("BAD %d\n", prime[i]);
                flag = false;
                break;
            }
        }
        if(flag) printf("GOOD\n");
    }
    return 0;
}
