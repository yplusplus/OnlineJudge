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
const int size = 4;
char map[10][10];
int chess_cnt;
int min_dfs();
int max_dfs();
int judge(char ch) {
    bool flag = true;
    int res = 0;
    for(int i = 0; i < size; i++) {
        flag = true;
        for(int j = 0; j < size; j++)
            if(map[i][j] != ch) flag = false;
        if(flag) res++;
        flag = true;
        for(int j = 0; j < size; j++)
            if(map[j][i] != ch) flag = false;
        if(flag) res++;
    }

    flag = true;
    for(int i = 0; i < size; i++)
        if(map[i][i] != ch) flag = false;
    if(flag) res++;

    flag = true;
    for(int i = 0; i < size; i++) 
        if(map[i][size - 1 - i] != ch) flag = false;
    if(flag) res++;
    return res;
}

int max_dfs() {
    int alpha = -inf;
    int res = judge('o');
    if(res > 0) return alpha;
    if(chess_cnt == 16) return 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(map[i][j] != '.') continue;
            map[i][j] = 'x';
            chess_cnt++;
            int tmp_alpha = min_dfs();
            map[i][j] = '.';
            chess_cnt--;
            alpha = max(alpha, tmp_alpha);
            if(alpha == inf) return alpha;
        }
    }
    return alpha;
}

int min_dfs() {
    int beta = inf;
    int res = judge('x');
    if(res > 0) return beta;
    if(chess_cnt == 16) return 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(map[i][j] != '.') continue;
            map[i][j] = 'o';
            chess_cnt++;
            int tmp_beta = max_dfs();
            map[i][j] = '.';
            chess_cnt--;
            beta = min(beta, tmp_beta);
            if(beta == -inf) return beta;
        }
    }
    return beta;
}

void isSureWin() {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(map[i][j] != '.') continue;
            map[i][j] = 'x';
            chess_cnt++;
            int alpha = min_dfs();
            if(alpha == inf) {
                printf("(%d,%d)\n", i, j);
                return;
            }
            map[i][j] = '.';
            chess_cnt--;
        }
    }
    puts("#####");
    return;
}
int main() {
    while(~scanf("%s", map[0])) {
        if(map[0][0] == '$') break;
        for(int i = 0; i < size; i++) scanf("%s", map[i]);
        chess_cnt = 0;
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                if(map[i][j] != '.') chess_cnt++;
        if(chess_cnt <= 4) {
            puts("#####");
            continue;
        }
        isSureWin();
    }
    return 0;
}
