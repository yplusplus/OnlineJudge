#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 234567;
int n;
int cnt[N], mu[N];
bool visit[N];
int tot, primes[N];

void precompute() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            primes[tot++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < tot && (long long)primes[j] * i < N; j++) {
            visit[primes[j] * i] = true;
            if (i % primes[j]) {
                mu[i * primes[j]] = -mu[i];
            } else {
                mu[i * primes[j]] = 0;
            }
        }
    }
}

int main() {
    precompute();
    while (~scanf("%d", &n)) {
        int m = 0;
        for (int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            cnt[x]++;
            m = max(m, x);
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 2; (long long)i * j <= m; j++) {
                cnt[i] += cnt[i * j];
            }
        }
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += (long long)mu[i] * cnt[i] * (cnt[i] - 1) / 2;
        }
        cout << ans << endl;
        memset(cnt, 0, sizeof(int) * (m + 1));
    }
    return 0;
}
