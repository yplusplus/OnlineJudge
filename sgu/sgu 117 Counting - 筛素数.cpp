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
const int MAX = 11111;
int prime[MAX], tot;
int cnt[MAX];
int cntK[MAX];
int n, m, k;
void getPrime() {
    bool isPrime[MAX];
    memset(isPrime, true, sizeof(isPrime));
    tot = 0;
    for(int i = 2; i < MAX; i++) {
        if(isPrime[i]) {
            prime[tot++] = i;
            for(int j = i * i; j < MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    getPrime();
    while(cin >> n >> m >> k) {
        int ans = 0;
        memset(cntK, 0, sizeof(cntK));
        for(int j = 0; j < tot; j++) {
            while(k % prime[j] == 0) {
                k /= prime[j];
                cntK[j]++;
            }
        }
        for(int i = 0, x; i < n; i++) {
            cin >> x;
            bool found = false;
            for(int j = 0; j < tot; j++) {
                cnt[j] = 0;
                while(x % prime[j] == 0) {
                    cnt[j]++;
                    x /= prime[j];
                }
                if(cnt[j] * m < cntK[j]) {
                    found = true;
                    break;
                }
            }
            if(!found) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
