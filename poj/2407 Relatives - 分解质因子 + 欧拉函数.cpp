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

const int N = 111111;
bool isPrime[N];
int prime[N], tot;
int n;

void getPrime() {
    tot = 0;
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i < N; i++) {
        if (isPrime[i]) {
            prime[tot++] = i;
            for (ll j = 1LL * i * i; j < N; j += i) isPrime[j] = false;
        }
    }
}

int main() {
    getPrime();
    while (cin >> n, n) {
        if (n == 1) {
            puts("0");
            continue;
        }
        ll ans = n;
        for (int i = 0; i < tot && n > 1; i++) {
            if (n % prime[i] == 0) {
                ans /= prime[i];
                ans *= prime[i] - 1;
                while (n % prime[i] == 0) n /= prime[i];
            }
        }
        if (n != 1) ans /= n, ans *= n - 1;
        cout << ans << endl;
    }
    return 0;
}
