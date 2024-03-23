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
const int TIMES = 555555;
int cnt[1 << 20];
int n;
int str[N];
int main() {
    cnt[0] = 0;
    for (int i = 0; i < 1 << 20; i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    int T;
    scanf("%d", &T);
    srand(time(NULL));
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%X", &str[i]);
        }
        int ans = inf;
        if (n <= 1111) {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    ans = min(ans, cnt[str[i] ^ str[j]]);
                }
            }
        } else {
            for (int i = 0; i < TIMES; i++) {
                int a = rand() % n, b = rand() % n;
                if (a != b) {
                    ans = min(ans, cnt[str[a] ^ str[b]]);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
