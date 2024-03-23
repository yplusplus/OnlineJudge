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
int a[N], b[N];
int main() {
    int n, x;
    while(~scanf("%d", &n)) {
        int ans = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            ans ^= a[i];
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
            ans ^= b[i];
        }
        for(int i = 0; i < n; i++) {
            a[i] ^= ans;
        }
        sort(a, a + n);
        sort(b, b + n);
        bool found = false;
        for(int i = 0; i < n; i++) {
            if(a[i] != b[i]) {
                found = true;
            }
        }
        printf("%d\n", found ? -1 : ans);
    }
    return 0;
}
