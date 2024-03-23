#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 1300000
int k;
int prime[100050], tot;
bool isprime[MAX];

void init() {
    tot = 0;
    memset(isprime, true, sizeof(isprime));
    for(int i = 2; i < MAX; i++) {
        if(isprime[i]) {
            prime[tot++] = i;
            if(i * i < MAX)
                for(int j = i + i; j < MAX; j += i) isprime[j] = false;
        }
    }
}

int main() {
    init();
    while(~scanf("%d", &k) && k) {
        if(isprime[k]) printf("0\n");
        else {
            int idx = upper_bound(prime, prime + tot, k) - prime;
            printf("%d\n", prime[idx] - prime[idx-1]);
        }
    }
    return 0;
}
