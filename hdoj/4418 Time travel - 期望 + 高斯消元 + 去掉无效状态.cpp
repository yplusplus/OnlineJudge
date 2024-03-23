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
const double eps = 1e-6;
const ll linf = 1LL << 55;

const int N = 222;
double mat[N][N];
double p[N];
int n, m, s, t, d;

bool gauss(int row, int col) {
    int i, j, r, c;
    for (r = c = 0; r < row && c < col; r++, c++) {
        int pvt = r;
        for (i = r + 1; i < row; i++) {
            if (fabs(mat[i][c]) > fabs(mat[pvt][c])) pvt = i;
        }
        if (fabs(mat[pvt][c]) < eps) { r--; continue; }
        if (pvt != r) {
            for (j = 0; j <= col; j++) swap(mat[pvt][j], mat[r][j]);
        }
        for (i = r + 1; i < row; i++) {
            double tmp = mat[i][c] / mat[r][c];
            for (j = c; j <= col; j++) {
                mat[i][j] -= mat[r][j] * tmp;
            }
        }
    }
    for (i = row - 1; i >= 0; i--) {
        if (fabs(mat[i][i]) < eps) {
            if (fabs(mat[i][col]) > eps) return false;
        } else {
            mat[i][col] /= mat[i][i];
            for (j = 0; j < i; j++) {
                mat[j][col] -= mat[j][i] * mat[i][col];
                mat[j][i] = 0;
            }
        }
    }
    return true;
}

int id[N];
bool visit[N];
int alloc;
bool bfs() {
    queue<int> que;
    memset(visit, 0, sizeof(visit));
    memset(id, -1, sizeof(id));
    alloc = 0;
    visit[s] = 1;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        id[u] = alloc++;
        for (int i = 1; i <= m; i++) {
            if (p[i] < eps) continue;
            int v = (u + i) % n;
            if (!visit[v]) {
                que.push(v);
                visit[v] = 1;
            }
        }
    }
    return visit[t] || visit[n - t];
}

void solve() {
    if (s == t) {
        puts("0.00");
        return;
    }
    n = n - 1 << 1;
    if (d == 1) s = n - s;
    if (!bfs()) {
        puts("Impossible !");
        return;
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < n; i++) {
        if (id[i] == -1) continue;
        mat[id[i]][id[i]] = 1;
        if (i == t || i == n - t) {
            mat[id[i]][alloc] = 0.0;
            continue;
        }
        for (int j = 1; j <= m; j++) {
            int pos = (i + j) % n;
            mat[id[i]][id[pos]] -= p[j];
            mat[id[i]][alloc] += p[j] * j;
        }
    }
    gauss(alloc, alloc);
    printf("%.2f\n", mat[id[s]][alloc]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d", &n, &m, &t, &s, &d);
        for (int i = 1; i <= m; i++) {
            scanf("%lf", &p[i]);
            p[i] /= 100.0;
        }
        solve();
    }
    return 0;
}
