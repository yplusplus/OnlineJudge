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

const int N = 1111;
int a[N][N];
int n, m;

int calc(int x, int y) {
    if(x < 1 || x > n || y < 1 || y > m) return inf;
    return a[x][y];
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &a[i][j]);
        for(int j = m; j >= 1; j--) {
            for(int i = n; i >= 1; i--) {
                a[i][j] = min(min(calc(i + 1, j), calc(i - 1, j + 1)), min(calc(i, j + 1), a[i][j]));
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                printf("%d%c", a[i][j], j == m ? '\n' : ' ');
            }
        }
    }
    return 0;
}
