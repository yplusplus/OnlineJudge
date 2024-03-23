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
#define kind 26
#define maxn 100050
char str[1111];
int num;
int in[kind], out[kind];
int s, t, n;
int maz[kind][kind];
void dfs(int u) {
    for(int i = 0; i < kind; i++) {
        if(!maz[u][i]) continue;
        maz[u][i]--;
        num++;
        dfs(i);
        //要输出方案就在这里用一个栈记录路径
    }
}
bool check() {
    s = t = -1;
    for(int i = 0; i < kind; i++) {
        if(in[i] != out[i]) {
            if(abs(in[i] - out[i]) != 1) return false;
            else {
                if(in[i] < out[i]) {
                    if(s != -1) return false;
                    s = i;
                } else {
                    if(t != -1) return false;
                    t = i;
                }
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(maz, 0, sizeof(maz));
        for(int i = 0; i < kind; i++)
            in[i] = out[i] = 0;
        int res = -1;
        for(int i = 0; i < n; i++) {
            scanf("%s", str);
            int u = str[0] - 'a', v = str[strlen(str)-1] - 'a';
            maz[u][v]++;
            out[u]++, in[v]++;
            res = u;
        }
        num = 0;
        if(!check()) puts("The door cannot be opened.");
        else {
            if(s == -1) s = res;
            dfs(s);
            if(num < n) puts("The door cannot be opened.");
            else puts("Ordering is possible.");
        }
    }
    return 0;
}
