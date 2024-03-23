#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
const int N = 222;
vector<pair<int, pii> > vec;
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool visit[N][N];
int maz[N][N];
pii que[N*N];
int head, tail;

//贪心
//刚开始从大到小贪发现不行，然后想了一下1肯定是最先放的
//所以从是1的开始贪，如果处理完这个点之后，有临近点变成1
//的话就继续放入队列处理，最后判断一下是否全部为0即可

bool check(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m;
}

bool bfs() {
    head = tail = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (maz[i][j] == 1) {
                que[tail++] = mp(i, j);
            }
        }
    }
    memset(visit, false, sizeof(visit));
    while (head < tail) {
        pii p = que[head++];
        maz[p.fi][p.se]--;
        visit[p.fi][p.se] = true;
        for (int i = 0; i < 4; i++) {
            int nx = p.fi + dx[i], ny = p.se + dy[i];
            if (check(nx, ny) && !visit[nx][ny]) {
                if (--maz[nx][ny] == 1) {
                    que[tail++] = mp(nx, ny);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (maz[i][j]) return false;
        }
    }
    return true;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> maz[i][j];
            }
        }
        if (bfs()) {
            reverse(que, que + n * m);
            for (int i = 0; i < n * m; i++) {
                cout << que[i].fi << " " << que[i].se << endl;
            }
        } else {
            puts("No solution");
        }
    }
    return 0;
}
