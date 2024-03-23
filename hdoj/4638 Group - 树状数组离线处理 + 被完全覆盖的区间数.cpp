#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 111111;
int n, m;
int c[N], pos[N];
int ans[N];
struct Interval {
    int a, b, c;
    void read() {
        scanf("%d%d", &a, &b);
    }
    Interval() {}
    Interval(int _a, int _b, int _c = -1) : a(_a), b(_b), c(_c) {}
    bool operator<(const Interval &x) const {
        return b < x.b;
    }
} e[2][N];

#define lowbit(x) (x & (-x))
void add(int x) {
    for (int i = x; i <= n; i += lowbit(i)) c[i]++;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += c[i];
    return res;
}
bool cmp(const pii &a, const pii &b) {
    return a.se < b.se;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x);
            pos[x] = i;
        }
        for (int i = 1; i < n; i++) {
            e[0][i].a = min(pos[i], pos[i + 1]);
            e[0][i].b = max(pos[i], pos[i + 1]);
        }
        sort(e[0] + 1, e[0] + n);
        for (int i = 0; i < m; i++) {
            e[1][i].read();
            e[1][i].c = i;
        }
        sort(e[1], e[1] + m);
        memset(c, 0, sizeof(c));
        int p = 1;
        int counter = 0;
        for (int i = 0; i < m; i++) {
            while (p < n && e[0][p].b <= e[1][i].b) {
                add(e[0][p].a);
                p++;
                counter++;
            }
            ans[e[1][i].c] = e[1][i].b - e[1][i].a + 1 - (counter - sum(e[1][i].a - 1));
        }
        for (int i = 0; i < m; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}

