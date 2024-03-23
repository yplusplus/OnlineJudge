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
const int N = 4;
int a[N][N], b[N][N], c[N][N];
int n;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

//搜索 + 剪枝
//每枚举完一位，就判断一下他上面的一位是否合法，这个剪枝效果很好。
//当然还有很多小剪枝。

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool check(int x, int y) {
    c[x][y] = 0;
    for(int k = 0; k < 4; k++) {
        int xx = x + dx[k], yy = y + dy[k];
        if(inside(xx, yy) && a[xx][yy] > a[x][y]) c[x][y]++;
    }
    return c[x][y] == b[x][y];
}

bool dfs(int x, int y) {
    if(x > n) {
        for(int i = 1; i <= n; i++)
            if(!check(n, i)) return false;
        return true;
    }
    int xx, yy;
    if(y + 1 > n) xx = x + 1, yy = 1;
    else xx = x, yy = y + 1;
    for(int k = 0; k <= 9; k++) {
        a[x][y] = k;
        if(x > 1) {
            if(!check(x - 1, y)) continue;
        }
        if(dfs(xx, yy)) return true;
    }
    return false;
}

int main() {
    while(cin >> n) {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                cin >> b[i][j];

        if(dfs(1, 1)) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }
        } else puts("NO SOLUTION");
    }
    return 0;
}
