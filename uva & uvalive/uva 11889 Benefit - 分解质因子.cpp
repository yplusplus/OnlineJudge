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
#define maxn 10010
bool ispri[maxn];
int pri[maxn], pn;
void get_pri() {
    memset(ispri, true, sizeof(ispri));
    pn = 0;
    pri[pn++] = 2;
    for(int i = 3; i < maxn; i += 2) {
        if(ispri[i]) {
            pri[pn++] = i;
            for(ll j = i * i; j < maxn; j += i) ispri[j] = false;
        }
    }
}

int main() {
    get_pri();
    int T;
    scanf("%d", &T);
    while(T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        bool flag = true;
        int ans = 1;
        for(int i = 0; i < pn; i++) {
            int cnt1 = 0, cnt2 = 0;
            int res = 1;
            if(a % pri[i] == 0) {
                while(a % pri[i] == 0) a /= pri[i], cnt1++;
            }
            if(b % pri[i] == 0) {
                while(b % pri[i] == 0) b /= pri[i], cnt2++, res *= pri[i];
            }
            if((b == 1 && a != 1) || cnt1 > cnt2) {
                flag = false;
                break;
            } else if(cnt1 < cnt2) ans *= res;
        }
        if(a != 1 && a != b) flag = false;
        if(a != b) ans *= b;
        if(flag) printf("%d\n", ans);
        else puts("NO SOLUTION");
    }
    return 0;
}
