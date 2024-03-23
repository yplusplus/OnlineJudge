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
int cnt[1<<20];
int n, k;
int main() {
    cnt[0] = 0;
    for(int mask = 1; mask < (1 << 20); mask++) {
        int j = 0;
        while(~mask >> j & 1) j++;
        cnt[mask] = cnt[mask ^ (1 << j)] + 1;
    }
    while(cin >> n >> k) {
        int mask = 0, preGray = 0;
        for(int mask = 1; mask < (1 << n); mask++) {
            int curGray = mask & (1 << n >> 1);
            for(int i = 0; i < n - 1; i++) {
                curGray |= ((mask >> i & 1) ^ (mask >> i >> 1 & 1)) << i;
            }
            if(cnt[curGray] > k) continue;
            int in = -1, out = -1;
            for(int j = 0; j < n; j++) {
                if((preGray >> j & 1) && (~curGray >> j & 1)) out = j;
                else if((~preGray >> j & 1) && (curGray >> j & 1)) in = j;
            }
            if(in != -1 && out != -1) {
                if(in > out) {
                    printf("++%d", out + 1);
                } else printf("--%d", out + 1);
            } else if(in != -1) {
                printf("+%d", in + 1);
            } else if(out != -1) {
                printf("-%d", out + 1);
            }
            preGray = curGray;
        }
        printf("-%d\n", n);
    }
    return 0;
}
