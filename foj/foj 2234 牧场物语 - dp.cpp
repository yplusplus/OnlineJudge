#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int N = 111;

LL dp[2 * N][N][N];
const int dx[] = {1, 0};
const int dy[] = {0, 1};
int n;
int a[N][N];

inline bool inmat(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }

inline void check_max(LL &a, LL b) { if (a < b) a = b; }

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 0; i < 2 * n - 1; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k <= i; k++) {
                    dp[i][j][k] = -(1LL << 60);
                }
            }
        }
        dp[0][0][0] = a[0][0];
        for (int i = 0; i < 2 * n - 1; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k <= i; k++) {
                    // (j, i - j) (k, i - k)
                    for (int u = 0; u < 2; u++) {
                        int ax = j + dx[u], ay = i - j + dy[u];
                        if (!inmat(ax, ay)) continue;
                        for (int v = 0; v < 2; v++) {
                            int bx = k + dx[v], by = i - k + dy[v];
                            if (!inmat(bx, by)) continue;
                            if (ax == bx && ay == by) {
                                check_max(dp[i + 1][ax][bx], dp[i][j][k] + a[ax][ay]);
                            } else {
                                check_max(dp[i + 1][ax][bx], dp[i][j][k] + a[ax][ay] + a[bx][by]);
                            }
                        }
                    }
                }
            }
        }
        cout << dp[2 * n - 2][n - 1][n - 1] << endl;
    }
    return 0;
}
