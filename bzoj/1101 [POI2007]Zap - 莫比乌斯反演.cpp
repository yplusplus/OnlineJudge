#include <iostream>
#include <cstdio>
using namespace std;

const int N = 50005;
int mu[N];
int primes[N], tot;
bool visit[N];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void init() {
    tot = 0;
    mu[0] = 0;
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            mu[i] = -1;
            primes[tot++] = i;
        }
        for (int j = 0; j < tot && (long long)primes[j] * i < N; j++) {
            visit[primes[j] * i] = true;
            if (i % primes[j]) {
                mu[primes[j] * i] = -mu[i];
            } else {
                mu[primes[j] * i] = 0;
                break;
            }
        }
    }
    for (int i = 2; i < N; i++) mu[i] += mu[i - 1];
}

int main() {
    init();
    int n, a, b, d;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a = read();
        b = read();
        d = read();
        //scanf("%d%d%d", &a, &b, &d);
        if (a > b) swap(a, b);
        long long ans = 0;
        a /= d;
        b /= d;
        for (int x = 1; x <= a; x++) {
            int y = min(a / (a / x), b / (b / x));
            ans += (long long)(mu[y] - mu[x - 1]) * (a / x) * (b / x);
            x = y;
        }
        printf("%d\n", (int)ans);
    }
    return 0;
}
