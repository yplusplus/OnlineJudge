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
ll product_mod(ll a, ll b, ll MOD) {
    ll res = 0;
    while(b) {
        if(b & 1) res = (res + a) % MOD;
        a = (a + a) % MOD;
        b >>= 1;
    }
    return res;
}
ll power_mod(ll a, ll b, ll MOD) {
    ll res = 1;
    while(b) {
        if(b & 1) {
            //res = res * a % MOD;
            res = product_mod(res, a, MOD);
        }
        //a = (a * a) % MOD;
        //如果a * a会溢出，用下面这个
        a = product_mod(a, a, MOD);
        b >>= 1;
    }
    return res;
}
int pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
bool MillerRabin(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (~n & 1) return false;
    int k = 0;
    ll m = n - 1;
    while (!(m & 1)) m >>= 1, k++;
    for (int i = 0; i < 10; i++) {
        if (pri[i] >= n) return true;
        ll a = power_mod(pri[i], m, n);
        if (a == 1) continue;
        int j;
        for (j = 0; j < k; j++) {
            if (a == n - 1) break;
            a = product_mod(a, a, n);
        }
        if (j == k) return false;
    }
    return true;
}

int main() {
    ll n;
    while(cin >> n) {
        if(MillerRabin(n)) puts("It is a prime number.");
        else puts("It is not a prime number.");
    }
    return 0;
}
