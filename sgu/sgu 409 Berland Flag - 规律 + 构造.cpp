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
int n, m;
const int N = 20 * 20;
char maz[N][N];

//规律构造题
//对于每个矩阵轮流以不同的点做起点，向右放连续k个*即可

int main() {
    while (cin >> n >> m) {
        memset(maz, '.', sizeof(maz));
        int offset = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x = j + i * n, y = j * n + i;
                for (int k = 0; k < m; k++) {
                    maz[x][(y + k) % (n * n)] = '*';
                }
            }
        }
        for (int i = 0; i < n * n; i++) {
            for (int j = 0; j < n * n; j++) {
                putchar(maz[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
