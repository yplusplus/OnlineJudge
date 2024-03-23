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
#define MAX 1000050
ll prime[5500], rec[MAX];
int tot, cnt;
bool isprime[MAX];
ll l, r;
void init() {
    tot = 0;
    memset(isprime, true, sizeof(isprime));
    prime[tot++] = 2;
    for(int i = 3; i < 50000; i += 2) {
        if(isprime[i]) {
            prime[tot++] = i;
            if(i * i < 50000) {
                for(int j = i + i; j < 50000; j += i) isprime[j] = false;
            }
        } 
    }
}

int main() {
    init();
    while(~scanf("%lld%lld", &l, &r)) {
        if(l < 2) l = 2;
        cnt = 0;
        memset(isprime, true, sizeof(isprime));
        for(int i = 0; i < tot && prime[i] * prime[i] <= r; i++) {
            ll tmp = l / prime[i] * prime[i];
            if(tmp < l) tmp += prime[i];
            if(tmp == prime[i]) tmp += prime[i];
            for(ll j = tmp; j <= r; j += prime[i]) isprime[j-l] = false;
        }
        for(int i = 0; i <= r - l; i++) 
            if(isprime[i]) rec[cnt++] = i + l;

        if(cnt < 2) printf("There are no adjacent primes.\n");
        else {
            int idx1 = 1, idx2 = 1;
            for(int i = 1; i < cnt; i++) {
                if(rec[i] - rec[i-1] < rec[idx1] - rec[idx1-1]) idx1 = i;
                if(rec[i] - rec[i-1] > rec[idx2] - rec[idx2-1]) idx2 = i;
            }
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", rec[idx1-1], rec[idx1], rec[idx2-1], rec[idx2]);
        }
    }
    return 0;
}
