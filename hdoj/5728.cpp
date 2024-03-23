#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

const int MOD = 1000000007;
const int N = 10000007;
int phi[N];
bool visit[N];
int primes[N], tot;
long long sum[N];
int min_primes[N];

void init() {
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            primes[tot++] = i;
            phi[i] = i - 1;
            min_primes[i] = i;
        }
        for (int j = 0; j < tot && (long long)primes[j] * i < N; j++) {
            visit[primes[j] * i] = 1;
            min_primes[primes[j] * i] = primes[j];
            if (i % primes[j]) {
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            } else {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) sum[i] = (phi[i] + sum[i - 1]) % MOD;
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

int calc(int k, int n) {
    if (n == 1) return 0;
    return power_mod(k, calc(k, phi[n]) + phi[n], n);
}

map<pair<int, int>, long long> table;
long long dfs(int n, int m) {
    if (m == 0) return 0;
    if (m == 1) return phi[n];
    if (n == 1) return sum[m];
    pair<int, int> k(n, m);
    if (table.count(k)) return table[k];
    int p = min_primes[n];
    return table[k] = (phi[p] * dfs(n / p, m) + dfs(n, m / p)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    int n, m, p;
    while (cin >> n >> m >> p) {
        cout << calc(dfs(n, m), p) << endl;
    }
    return 0;
}
