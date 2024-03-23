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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 55;
int maz[N][N];
int color[N];
int n, m;
int main() {
    while (cin >> n >> m) {
        char str[5];
        for (int i = 1; i <= n; i++) {
            cin >> str;
            color[i] = str[0] == 'E';
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                maz[i][j] = inf;
            }
            maz[i][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            maz[a][b] = maz[b][a] = color[a] != color[b];
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
                }
            }
        }
        int pos = 0, rec = n + 1;
        for (int i = 1; i <= n; i++) {
            int t = *max_element(maz[i] + 1, maz[i] + 1 + n);
            if (t < rec) rec = t, pos = i;
        }
        cout << rec << endl;
        for (int i = 0; i < rec; i++) {
            cout << pos << " " << (color[pos] ? 'J' : 'E') << endl;
            color[pos] ^= 1;
        }
    }
    return 0;
}
