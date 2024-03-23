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

const int MAX = 11111;
char str[MAX];
char t[MAX];
int solve(char s[]) {
    set<pair<ull, ull> >words;
    int len = strlen(s);
    s[len++] = ' ';
    int tot = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            if (!tot) continue;
            ull a = 0, b = 0;
            for (int i = 0; i < tot; i++) {
                a = 23 * a + t[i] - 'a' + 1;
                b = 31 * b + t[i] - 'a' + 1;
            }
            words.insert(mp(a, b));
            tot = 0;
        } else {
            t[tot++] = s[i];
        }
    }
    return words.size();
}

int main() {
    while(1) {
        gets(str);
        if (str[0] == '#') break;
        printf("%d\n", solve(str));
    } 
    return 0;
}
