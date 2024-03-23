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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
int max_dfs(int alpha, int beta);
int min_dfs(int alpha, int beta);
int acnt, bcnt, n;
int limit, mask, cnt;
int tri[20][5] = {{0}, {2, 3}, {1, 3}, {1, 2, 5, 7}, {5, 6}, {4, 6, 3, 7}, {4, 5, 11, 13}, {3, 5, 8, 9}, {7, 9}, {7, 8, 14, 16}, {11, 12},
    {10, 12, 6, 13}, {10, 11}, {6, 11, 14, 15}, {13, 15, 9, 16}, {13, 14}, {9, 14, 17, 18}, {16, 18}, {16, 17}};

int tt[9][3] = {{1, 2, 3}, {4, 5, 6}, {3, 5, 7}, {7, 8, 9}, {10, 11, 12}, {6, 11, 13}, {13, 14, 15}, {9, 14, 16}, {16, 17, 18}};

int check(int x) {
    int tmp = 0;
    tmp += ((mask & (1 << tri[x][0])) && (mask & (1 << tri[x][1])));
    tmp += ((mask & (1 << tri[x][2])) && (mask & (1 << tri[x][3])));
    return tmp;
}

int max_dfs(int alpha, int beta) {
    alpha = -inf;
    if(cnt == 0) {
        if(acnt > bcnt) return -inf;
        else if(acnt < bcnt) return inf;
        else return 0;
    }
    for(int i = 1; i <= 18; i++) {
        if(!(mask & (1 << i))) {
            int res = check(i);
            if(acnt + res >= limit) {
                alpha = inf;
                break;
            }
            acnt += res;
            cnt--;
            mask |= (1 << i);
            if(res > 0) alpha = max(alpha, max_dfs(-inf, inf));
            else alpha = max(alpha, min_dfs(alpha, inf));
            mask ^= (1 << i);
            cnt++;
            acnt -= res;
            if(alpha >= beta) break;
        }
    }
    return alpha;
}

int min_dfs(int alpha, int beta) {
    beta = inf;    
    if(cnt == 0) {
        if(acnt > bcnt) return inf;
        else if(acnt < bcnt) return -inf;
        else return 0;
    }
    for(int i = 1; i <= 18; i++) {
        if(!(mask & (1 << i))) {
            int res = check(i);
            if(bcnt + res >= limit) {
                beta = -inf;
                break;
            }
            bcnt += res;
            cnt--;
            mask |= (1 << i);
            if(res > 0) beta = min(beta, min_dfs(-inf, inf));
            else beta = min(beta, max_dfs(-inf, beta));
            mask ^= (1 << i);
            cnt++;
            bcnt -= res;
            if(beta <= alpha) break;
        }
    }
    return beta;
}

int main() {
    int T;
    scanf("%d", &T);
    int line[12][12];
    line[1][2] = 1; line[1][3] = 2;
    line[2][3] = 3; line[2][4] = 4; line[2][5] = 5;
    line[3][5] = 7; line[3][6] = 8;
    line[4][5] = 6; line[4][7] = 10; line[4][8] = 11;
    line[5][6] = 9; line[5][8] = 13; line[5][9] = 14;
    line[6][9] = 16; line[6][10] = 17;
    line[7][8] = 12;
    line[8][9] = 15;
    line[9][10] = 18;
    int Case = 1;
    while(T--) {
        scanf("%d", &n);
        mask = 0;
        cnt = 18 - n;
        int id = 0;
        int num[2];
        num[0] = num[1] = 0;
        for(int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(a > b) swap(a, b);
            int res = check(line[a][b]);
            if(res) num[id] += res;
            else id ^= 1;
            mask |= (1 << line[a][b]);
        }
        limit = 5;
        int alpha = -inf;
        acnt = num[0], bcnt = num[1];
        if(acnt >= 5 || bcnt >= 5) {
            if(acnt >= 5) alpha = inf;
            else alpha = -inf;
        } else if(id) {
            alpha = min_dfs(-inf, inf);
        } else {
            alpha = max_dfs(-inf, inf);
        }
        printf("Game %d: %c wins.\n", Case++, (alpha == inf) ? 'A' : 'B');
    }
}
