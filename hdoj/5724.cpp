#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int M = 20;
int sg[1 << M];
int n;
bool visit[M];

int main() {

    // calc
    for (int mask = 0; mask < (1 << M); mask++) {
        int last_empty = -1;
        memset(visit, 0, sizeof(visit));
        for (int i = 0; i < M; i++) {
            if (mask & (1 << i)) {
                if (last_empty != -1) {
                    visit[sg[mask ^ (1 << i) ^ (1 << last_empty)]] = 1;
                }
            } else {
                last_empty = i;
            }
        }
        int c = 0;
        while (visit[c]) c++;
        sg[mask] = c;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int xor_sum = 0;
        for (int i = 1, k; i <= n; i++) {
            scanf("%d", &k);
            int mask = 0;
            for (int j = 0, x; j < k; j++) {
                scanf("%d", &x);
                mask |= 1 << (M - x);
            }
            xor_sum ^= sg[mask];
        }
        puts(xor_sum > 0 ? "YES" : "NO");
    }
    return 0;
}
