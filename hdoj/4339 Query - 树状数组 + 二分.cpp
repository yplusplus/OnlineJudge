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
#define MAX 1000050
int sum[MAX];
char s[3][MAX];
int len;
void update(int x, int val) {
    for(int i = x; i <= len; i += lowbit(i))
        sum[i] += val;
}

int query(int x) {
    int res = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        res += sum[i];
    return res;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%s%s", s[1] + 1, s[2] + 1);
        memset(sum, 0, sizeof(sum));
        len = min(strlen(s[1] + 1), strlen(s[2] + 1));
        for(int i = 1; i <= len; i++) {
            if(s[1][i] == s[2][i]) update(i, 1);
        }
        int q, op, x, who, length;
        scanf("%d", &q);
        printf("Case %d:\n", Case++);
        char ch[5];
        while(q--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d%d%s", &who, &length, ch);
                length++;
                if(length > len) continue;
                bool before = s[1][length] == s[2][length];
                s[who][length] = ch[0];
                bool after = s[1][length] == s[2][length];
                if(before ^ after) {
                    update(length, after ? 1 : -1);
                }
            } else {
                scanf("%d", &x);
                x++;
                if(s[1][x] != s[2][x]) puts("0");
                else {
                    int l = x, r = len;
                    int rec = query(x - 1);
                    int ans = -1;
                    while(l <= r) {
                        int mid = (l + r) >> 1;
                        if(query(mid) - rec == mid - x + 1) ans = mid, l = mid + 1;
                        else r = mid - 1;
                    }
                    printf("%d\n", ans - x + 1);
                }
            }
        }
    }
    return 0;
}
