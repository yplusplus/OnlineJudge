#include <iostream>
#include <cstdio>
using namespace std;

const int N = 10000007;
int phi[N];
bool visit[N];
int primes[N], tot;

void init() {
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            primes[tot++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < tot && (long long)primes[j] * i < N; j++) {
            visit[primes[j] * i] = 1;
            if (i % primes[j]) {
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            } else {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            }
        }
    }
}

int power_mod(long long a, long long b, int mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return (int)res;
}

int calc(int n) {
    if (n == 1) return 0;
    return power_mod(2, calc(phi[n]) + phi[n], n);
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << calc(n) << endl;
    }
    return 0;
}
