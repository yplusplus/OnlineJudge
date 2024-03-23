#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int n, m, sum;
int maz[15][15];

bool check(int x, int y) {
    if(x >= 1 && x <= n && y >= 1 && y <= m) return true;
    return false;
}

bool solve() {
    if(sum == n * m) return false;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(!maz[i][j])
                for(int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if(!check(x, y)) continue;
                    if(!maz[x][y]) return false;
                }
    return true;
}

int main() {
    while(cin >> n >> m) {
        if(!n && !m) break;
        sum = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++) {
                cin >> maz[i][j];
                sum += maz[i][j];
            }
        if(solve()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
