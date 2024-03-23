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

const int N = 2;

int dir[N], s[N], t[N];
pii node[N];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
char w[256];
int n, k;

bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int main() {
    w['W'] = 0, w['S'] = 1, w['E'] = 2, w['N'] = 3;
    while (~scanf("%d", &n), n) {
        char ch[5];
        for (int i = 0; i < N; i++) {
            scanf("%s%d%d", ch, &s[i], &t[i]);
            dir[i] = w[ch[0]];
        }
        scanf("%d", &k);
        node[0] = mp(1, 1);  
        node[1] = mp(n, n);
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < N; j++) {
                for (int l = 0; l < s[j]; l++) {
                    int x = node[j].fi + dx[dir[j]];
                    int y = node[j].se + dy[dir[j]];
                    if (check(x, y)) {
                        node[j] = mp(x, y);
                    } else {
                        if (dir[j] & 1) dir[j] = 4 - dir[j];
                        else dir[j] = 2 - dir[j];
                        l--;
                    }
                }
            }
            if (node[0] == node[1]) {
                swap(dir[0], dir[1]);
            } else {
                for (int j = 0; j < N; j++) {
                    if (i % t[j] == 0) {
                        dir[j] = (dir[j] + 1) % 4;
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            cout << node[i].fi << " " << node[i].se << endl;
        }
    }
    return 0;
}
