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
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 9989900
int rec[1050];
bool isprime[maxn];
int pn;

bool check(int x) {
    int tmp = x;
    int res = 0;
    while(tmp) {
        res *= 10;
        res += tmp % 10;
        tmp /= 10;
    }
    return res == x;
}

void getprime() {
    memset(isprime, true, sizeof(isprime));
    pn = 0;
    for(ll i = 3; i < maxn; i += 2) {
        if(isprime[i]) {
            if(check(i)) rec[pn++] = i;
            for(ll j = i * i; j < maxn; j += i) isprime[j] = false;
        }
    }
}



int main() {
    getprime();
    int a, b;
    while(~scanf("%d%d", &a, &b)) {
        for(int i = 1; i < pn; i++) {
            if(rec[i] > b) break;
            if(rec[i] >= a) printf("%d\n", rec[i]);
        }
        printf("\n");
    }
    return 0;
}
