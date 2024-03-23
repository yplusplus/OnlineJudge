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
const int MAX = 1000001;
int a, b;
bool isPrime[MAX];
int prime[MAX], tot;
void getPrime() {
    memset(isPrime, true, sizeof(isPrime));
    tot = 0;
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            prime[tot++] = i;
            for (ll j = 1LL * i * i; j < MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
int main() {
    getPrime();
    while (cin >> a >> b) {
        int sumA = 0, sumB = 0;
        int maxA = 0, maxB = 0;
        for (int i = 0; i < tot; i++) {
            if (a % prime[i] == 0) {
                sumA += maxA;
                maxA = prime[i];
            }
            if (b % prime[i] == 0) {
                sumB += maxB;
                maxB = prime[i];
            }
        }
        int delta = (maxA - sumA) - (maxB - sumB);
        puts(delta > 0 ? "a" : "b");
    }
    return 0;
}
