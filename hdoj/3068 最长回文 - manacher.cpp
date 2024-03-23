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

const int N = 111111;
char str[N];
char s[N << 1];
int p[N << 1];
int manacher(char str[]) {
    int tot = 0, len = strlen(str), res = 0;
    s[tot++] = '$';
    s[tot++] = '#';
    for (int i = 0; i < len; i++) s[tot++] = str[i], s[tot++] = '#';
    s[tot] = 0;
    int pos = 0, mx = 0;
    for (int i = 1; i < tot; i++) {
        p[i] = mx > i ? min(p[2 * pos - i], mx - i) : 1;
        while (s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (mx < i + p[i]) {
            pos = i, mx = i + p[i];
        }
        //cout << s[i] << " " << p[i] << endl;
        if (i & 1) res = max(res, p[i] / 2 * 2);
        else res = max(res, (p[i] - 1) / 2 * 2 + 1);
    }
    return res;
}

int main() {
    while (~scanf("%s", str)) {
        printf("%d\n", manacher(str));
    }
    return 0;
}
