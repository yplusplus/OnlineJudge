#include <iostream>
using namespace std;

const int N = 11111111;
bool visit[N];
int primes[N], tot;
long long phi[N];

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

int main() {
    init();
    for (int i = 2; i < N; i++) phi[i] += phi[i - 1];
    int n;
    while (cin >> n) {
        long long ans = 0;
        for (int i = 0; i < tot && primes[i] <= n; i++) {
            ans += phi[n / primes[i]] * 2LL - 1;
        }
        cout << ans << endl;
    }
    return 0;
}
