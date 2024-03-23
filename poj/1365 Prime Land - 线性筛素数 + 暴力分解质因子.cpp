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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
char c;
int cnt;
int rec[10000], num[10000];
int prime[10000], tot;

int getint() {
    c = getchar();
    int tmp = 0;
    while(c != ' ' && c != 10) {
        tmp = tmp * 10 + c - '0';
        c = getchar();
    }
    return tmp;
}

void init() {
    bool isprime[33000];
    tot = 0;
    memset(isprime, true, sizeof(isprime));
    prime[tot++] = 2;
    for(int i = 3; i < 33000; i += 2) {
        if(isprime[i]) {
            prime[tot++] = i;
            if(i * i < 33000)
                for(int j = i + i; j < 33000; j += i) isprime[j] = false;
        }
    }
}

ll power(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

void solve(ll x) {
    cnt = 0;
    for(int i = 0; i < tot && x > 1; i++) {
        if(x % prime[i] == 0) {
            rec[cnt] = prime[i], num[cnt] = 0;
            while(x % prime[i] == 0) num[cnt]++, x /= prime[i];
            cnt++;
        }
    }
    for(int i = cnt - 1; i >= 0; i--) {
        printf("%d %d ", rec[i], num[i]);
    }
    printf("\n");

}

int main() {
    init();
    while(1) {
        ll x = 1;
        cnt = 0;
        rec[cnt] = getint();
        if(rec[0] == 0) break;
        num[cnt++] = getint();
        while(c != 10) rec[cnt] = getint(), num[cnt++] = getint();
        for(int i = 0; i < cnt; i++)
            x *= power(rec[i], num[i]);
        solve(x - 1);
    }
    return 0;
}
