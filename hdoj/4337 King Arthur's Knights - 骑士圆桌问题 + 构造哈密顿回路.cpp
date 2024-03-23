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
const int maxn = 200;
bool maz[maxn][maxn], vist[maxn];
int s, t, len, tot, p, n;
int ans[2][maxn];
void expand(int x) {
    bool flag;
    do {
        flag = false;
        if (!vist[x]) ans[p][tot++] = x;
        vist[x] = true;
        for (int i = 0; i < n; i++)
            if (maz[x][i] && !vist[i]) {
                x = i, flag = true;
                break;
            }
    } while (flag);
}
void init() {
    memset(vist, false, sizeof (vist));
    s = t = len = tot = p = 0;
    expand(s); //源点扩展
    reverse(ans[p], ans[p] + tot); //反向
    expand(t); //汇点扩展
    len = tot; //更新长度
    s = ans[p][0], t = ans[p][len - 1];
}
void hamilton() {
    init(); //初始的时候先随意定义一个源汇点扩展
    int i, j;
    while (len < n || !maz[s][t]) {
        if (maz[s][t]) {//环变链
            int u = -1, v = -1;
            for (i = 0; u == -1 && i < len; i++) {//找一个新的点假如到环中
                for (j = 0; j < n; j++) {
                    if (!vist[j] && maz[ans[p][i]][j]) {
                        u = i, v = j;
                        break;
                    }
                }
            }
            //下面是调整环，更新成一条点数多一的链
            p = !p, tot = 0;
            for (i = u + 1; i < len; i++)
                ans[p][tot++] = ans[!p][i];
            for (i = 0; i <= u; i++)
                ans[p][tot++] = ans[!p][i];
            ans[p][tot++] = v;
            vist[v] = true, len++;
        } else {//由链边环
            for (i = 1; i < len; i++) {
                if (maz[s][ans[p][i]] && maz[t][ans[p][i - 1]]) break;
            }
            reverse(ans[p] + i, ans[p] + len); //取到一个可以成环的点，就更新链成环
        }
        s = ans[p][0], t = ans[p][len - 1];
    }
}
int main() {
    int a, b, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) break;
        memset(maz, false, sizeof (maz));
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);
            --a, --b;
            maz[a][b] = maz[b][a] = true;
        }
        for (int i = 0; i < n; i++) maz[i][i] = false;
        hamilton(); //哈密顿回路构造
        for (int i = 0; i < len - 1; i++) {
            printf("%d ", ans[p][i] + 1);
        }
        printf("%d\n", ans[p][len - 1] + 1);
    }
    return 0;
}
