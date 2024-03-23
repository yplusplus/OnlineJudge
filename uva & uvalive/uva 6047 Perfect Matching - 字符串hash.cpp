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
const int N = 1111;
const int MOD = 1870667;
char str[N][N];
int len[N];
int n;
ull val[N], fac[N], rval[N];
const int magic = 131;
ull RKHash(char *str) {
    ull hash = 0;
    while (*str) {
        hash = (hash * magic) + (*str - 'a' + 1);
        str++;
    }
    return hash;
}

bool check(int i, int j) {
    ull tmp = val[i] * fac[len[j]] + val[j];
    ull tmp2 = rval[j] * fac[len[i]] + rval[i];
    return tmp == tmp2;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * magic;
    }
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            scanf("%s", str[i]);
            len[i] = strlen(str[i]);
            val[i] = RKHash(str[i]);
            reverse(str[i], str[i] + len[i]);
            rval[i] = RKHash(str[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && check(i, j)) ans++;
            }
        }
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
