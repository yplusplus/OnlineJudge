#include <iostream>
#include <cstdio>
using namespace std;

const int N = 10000010;
int primes[N], tot;
bool visit[N];
int mu[N];
int f[N];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void init() {
    tot = 0;
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            primes[tot++] = i;
            mu[i] = -1;
            f[i] = 1;
        }
        for (int j = 0; j < tot && (long long)primes[j] * i < N; j++) {
            visit[primes[j] * i] = 1;
            if (i % primes[j]) {
                f[primes[j] * i] = mu[i] - f[i];
                mu[primes[j] * i] = -mu[i];
            } else {
                if (i / primes[j] % primes[j] == 0) f[primes[j] * i] = 0;
                else f[primes[j] * i] = mu[i];
                mu[primes[j] * i] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) f[i] += f[i - 1];
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        n = read();
        m = read();
        //scanf("%d%d", &n, &m);
        if (n > m) swap(n, m);
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            int y = min(n / (n / i), m / (m / i));
            ans += (long long)(n / i) * (m / i) * (f[y] - f[i - 1]);
            i = y;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
