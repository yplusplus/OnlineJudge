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
string h[N];
int n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
char height(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m) return '0';
    else return h[x][y];
}

int main() {
    while(cin >> n >> m) {
        for(int i = 0; i < n; i++) cin >> h[i];
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(h[i][j] - '0') ans += 2;
                for(int k = 0; k < 4; k++) {
                    int ii = i + dx[k], jj = j + dy[k];
                    ans += max(h[i][j] - height(ii, jj), 0);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
