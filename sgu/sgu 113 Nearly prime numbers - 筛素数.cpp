#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 50050
int pri[maxn], pn;
int n;
void getPrime() {
    bool ispri[maxn];
    memset(ispri, true, sizeof(ispri));
    pn = 0;
    pri[pn++] = 2;
    for(ll i = 3; i < maxn; i += 2) {
        if(ispri[i]) {
            pri[pn++] = i;
            for(ll j = i * i; j < maxn; j += i) ispri[j] = false;
        }
    }
}

bool check(int x) {
    int cnt = 0;
    for(int i = 0; i < pn; i++) {
        while(x % pri[i] == 0) {
            cnt++;
            x /= pri[i];
        }
    }
    if(x != 1) cnt++;
    return cnt == 2;
}

int main() {
    getPrime();
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        if(check(n)) puts("Yes");
        else puts("No");
    }
    return 0;
}
