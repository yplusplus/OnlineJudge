#include <iostream>
#include <cmath>
using namespace std;

double paint(int x, int n) {
    double p = (2.0 * x * (n - x + 1) - 1) / n / n;
    return p;
}

double not_paint(int x, int y, int n, int m, int k) {
    double p = paint(x, n) * paint(y, m);
    return pow(1 - p, k);
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        double ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                ans += 1 - not_paint(i, j, n, m, k);
            }
        }
        //cout << ans << endl;
        printf("Case #%d: %.0f\n", Case++, ans);
    }
    return 0;
}
