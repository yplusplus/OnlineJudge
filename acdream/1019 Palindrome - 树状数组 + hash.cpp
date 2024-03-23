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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 1000007;
char str[N];

ull c[N][2], fac[N];
int n, m;
void init() {
    memset(c, 0, sizeof(c));
}

void add(int x, ull val, int idx) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c[i][idx] += val;
    }
}

ull sum(int x, int idx) {
    ull res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += c[i][idx];
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * 31;
    }
    while (~scanf("%s", str)) {
        init();
        n = strlen(str);
        for (int i = 1; i <= n; i++) {
            int j = n + 1 - i;
            ull tmp;
            tmp = str[i - 1] - 'a' + 1;
            add(i, tmp * fac[i - 1], 0);
            add(j, tmp * fac[j - 1], 1);
        }
        scanf("%d", &m);
        while (m--) {
            char op[10];
            scanf("%s", op);
            if (op[0] == 'Q') {
                int a, b, c, d;
                scanf("%d%d", &a, &b);
                if (a > b) swap(a, b);
                c = n + 1 - b, d = n + 1 - a;
                ull h1 = (sum(b, 0) - sum(a - 1, 0)) * fac[c - 1];
                ull h2 = (sum(d, 1) - sum(c - 1, 1)) * fac[a - 1];
                puts(h1 == h2 ? "yes" : "no");
            } else if (op[0] == 'C') {
                int a;
                char ch[5];
                scanf("%d%s", &a, ch);
                int b = n + 1 - a;
                add(a, (ch[0] - str[a - 1]) * fac[a - 1], 0);
                add(b, (ch[0] - str[a - 1]) * fac[b - 1], 1); 
                str[a - 1] = ch[0];
            }
        }
    }
    return 0;
}
