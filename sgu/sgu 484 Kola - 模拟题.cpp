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
const int N = 111;
char maz[N][N];
int n, m;
int fall(int x, int y) {
    if(y == 0 || y == m + 1) return -1;
    if(x == n + 1) return y;
    //handle
    if(maz[x+1][y] == '.') return fall(x + 1, y);
    if(maz[x+1][y] == '/') {
        if(maz[x+1][y-1] == '\\') return -1;
        else return fall(x + 1, y - 1);
    } else {
        if(maz[x+1][y+1] == '/') return -1;
        else return fall(x + 1, y + 1);
    }
}
int main() {
    while(cin >> n >> m) {
        memset(maz, '.', sizeof(maz));
        for(int i = 1; i <= n; i++) scanf("%s", &maz[i][1]);
        for(int i = 1; i <= n; i++) maz[i][m+1] = '.';
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(maz[i][j] == 'P') {
                    cout << fall(i, j) << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
