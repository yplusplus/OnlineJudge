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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

#define maxn 1000050

ll phi[maxn], sum[maxn];
int n;
void init() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    sum[1] = 0;
    for(ll i = 2; i < maxn; i++) {
        if(!phi[i]) {
            for(ll j = i; j < maxn; j += i) {
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
        sum[i] = sum[i-1] + phi[i];
    }
}

int main() {
    init();
    while(~scanf("%d", &n)) {
        if(!n) break;
        else cout << sum[n] << endl;
    }
    return 0;
}
