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
#define eps 1e-6
char maz[20][20];
int id[20][20];
int n, m, tot;
int sx, sy;
bool visit[20][20];
double mat[300][300], x[300];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool check(int x, int y) {
    if(x >= 0 && x < n && y >= 0 && y < m && maz[x][y] != '#') {
        return true;
    } else {
        return false;
    }
}

inline int dcmp(double d) {
    return (d < -eps) ? -1 : (d > eps);
}
//row 行数，col 列数 x[i] 变量i的值
bool gauss(int row, int col) {
    int r , c , i , j;
    for(r = c = 0; r < row && c < col; r++, c++) {
        for(i = r ; i < row ; i ++) if(dcmp(mat[i][c]) != 0) break;
        if(i == row) {r--; continue;}
        if(i != r) {
            for(j = c ; j <= col ; j ++)
                swap(mat[i][j],mat[r][j]);
        }
        for(i = r + 1; i < row; i++) {
            if(dcmp(mat[i][c]) != 0) {
                double temp = mat[i][c] / mat[r][c];
                for(j = c; j <= col; j++) mat[i][j] -= mat[r][j] * temp;
            }
        }
    }
    for(i = row - 1 ; i >= 0 ; i --) {
        if(dcmp(mat[i][i]) != 0) x[i] = mat[i][col] / mat[i][i];
        else {
            if(dcmp(mat[i][col]) == 0) x[i] = 0.0;
            else return false;//无解
        }
        for(j = 0; j < i; j++) mat[j][col] -= mat[j][i] * x[i];
    }
    return true;
}

bool bfs() {
    tot = 0;
    memset(visit, false, sizeof(visit));
    memset(id, -1, sizeof(id));
    queue<int> que;
    que.push(sx);
    que.push(sy);
    visit[sx][sy] = true;
    id[sx][sy] = tot++;
    bool found = false;
    int x, y;
    while(!que.empty()) {
        x = que.front(), que.pop();
        y = que.front(), que.pop();
        if(maz[x][y] == '$') {
            found = true;
            continue;
        }
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(!check(nx, ny)) continue;
            if(id[nx][ny] == -1) id[nx][ny] = tot++;
            if(!visit[nx][ny]) {
                que.push(nx);
                que.push(ny);
                visit[nx][ny] = true;
            }
        }
    }
    return found;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 0; i < n; i++) {
            scanf("%s", maz[i]);
            for(int j = 0; j < m; j++) {
                if(maz[i][j] == '@') sx = i, sy = j;
            }
        }
        //cout << tot << endl;
        memset(mat, 0, sizeof(mat));
        if(!bfs()) {
            cout << -1 << endl;
        } else {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(id[i][j] == -1) continue;
                    int idx = id[i][j];
                    if(maz[i][j] == '$') {
                        mat[idx][idx] = 1.0;
                        continue;
                    }
                    int cnt = 0;
                    for(int k = 0; k < 4; k++) {
                        int ii = i + dx[k], jj = j + dy[k];
                        if(check(ii, jj)) {
                            mat[idx][id[ii][jj]] = 1.0;
                            cnt++;
                        }
                    }
                    mat[idx][tot] = -1.0 * cnt;
                    mat[idx][idx] = -1.0 * cnt;
                }
            }
            gauss(tot, tot);
            printf("%.6f\n", x[0]);
        }
    }
    return 0;
}
