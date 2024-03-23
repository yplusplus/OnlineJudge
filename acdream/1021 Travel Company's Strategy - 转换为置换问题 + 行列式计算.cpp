#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 111;
int mat[N][N], n, m;

int calc_det(int mat[][N], int n) {
    for (int i = 0; i < n; i++) {
        int pivot = -1;
        for (int j = i; j < n; j++) {
            if (mat[j][i]) {
                pivot = j;
                break;
            }
        }
        if (pivot == -1) return 0;
        if (pivot != i) {
            for (int j = 0; j < n; j++) swap(mat[i][j], mat[pivot][j]);
        }
        for (int j = i + 1; j < n; j++) {
            if (mat[j][i]) {
                for (int k = 0; k < n; k++) {
                    mat[j][k] ^= mat[i][k];
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!mat[i][i]) return 0;
    }
    return 1;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            mat[u][v] = 1;
        }
        int ans = calc_det(mat, n);
        cout << ans << endl;
    }
    return 0;
}
