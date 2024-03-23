#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int id[20][20];
int dp[1 << 12][10];
int map[1 << 12];
int has, tot;
int grid[15] = {153, 306, 612, 19584, 39168, 78336, 2506752, 5013504, 10027008};
int edge[30];
int n;

int dfs(int mask, int sum) {
    if (dp[mask][sum] != -1) return dp[mask][sum];
    if (sum == 0) return dp[mask][sum] = 0;
    int res = 0;
    for (int i = 0; i < tot; i++) {
        if (~mask >> i & 1) {
            int t = has | map[mask] | edge[i];
            int v = 0;
            for (int j = 0; j < 9; j++) {
                if ((grid[j] & edge[i]) && (t & grid[j]) == grid[j]) v++;
            }
            res = max(res, sum - dfs(mask | (1 << i), sum - v));
        }
    }
    return dp[mask][sum] = res;
}

int main() {
    id[1][2] = 0, id[2][3] = 1, id[3][4] = 2;
    id[5][6] = 7, id[6][7] = 8, id[7][8] = 9;
    id[9][10] = 14, id[10][11] = 15, id[11][12] = 16;
    id[13][14] = 21, id[14][15] = 22, id[15][16] = 23;
    id[1][5] = 3, id[2][6] = 4, id[3][7] = 5, id[4][8] = 6;
    id[5][9] = 10, id[6][10] = 11, id[7][11] = 12, id[8][12] = 13;
    id[9][13] = 17, id[10][14] = 18, id[11][15] = 19, id[12][16] = 20;
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        tot = has = 0;
        int tom = 0, jerry = 0;
        scanf("%d", &n);
        int sum = 9;
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a > b) swap(a, b);
            has |= 1 << id[a][b];
            for (int j = 0; j < 9; j++) {
                if ((grid[j] >> id[a][b] & 1) && ((has & grid[j]) == grid[j])) {
                    if (i & 1) jerry++;
                    else tom++;
                    sum--;
                }
            }
        }
        for (int i = 0; i < 24; i++) {
            if (~has >> i & 1) {
                edge[tot++] = 1 << i;
            }
        }
        memset(map, 0, sizeof(map));
        for (int i = 0; i < (1 << tot); i++) {
            for (int j = 0; j < tot; j++) {
                if (i >> j & 1) map[i] |= edge[j];
            }
        }
        memset(dp, -1, sizeof(dp));
        if (~n & 1) {
            tom += dfs(0, sum);
            jerry += sum - dfs(0, sum);
        } else {
            tom += sum - dfs(0, sum);
            jerry += dfs(0, sum);
        }
        printf("Case #%d: %s\n", Case++, (tom > jerry) ? "Tom200" : "Jerry404");
    }
    return 0;
}

