#include <iostream>
#include <cstdio>
using namespace std;

double p;
int x, n;
const int N = 111111;
double f[N];

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lf%d", &n, &p, &x);
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
            f[i] = 1e300;
            double g = 1 / (1 - p);
            for (int j = 1; j <= i; j++) {
                f[i] = min(f[i], f[i - j] + g + x);
                g = (g + 1) / (1 - p);
                if (g > f[i]) break;
            }
        }
        printf("Case #%d: %.6f\n", Case++, f[n]);
    }
    return 0;
}
