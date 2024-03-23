#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 111111;
bool visit[N];
int a[N];
int cnt[N];
int n, k;

int main() {
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 0; i < n; i++) { scanf("%d", &a[i]); }
        memset(visit, false, sizeof(visit));
        memset(cnt, 0, sizeof(cnt));
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (visit[i]) continue;
            if (a[i] == i) {
                ans++;
                continue;
            }
            int t = 0, x = i;
            while (!visit[x]) {
                t++;
                visit[x] = true;
                x = a[x];
            }
            cnt[t]++;
        }
        for (int i = 1; i <= n && k; i++) {
            if (cnt[i] == 0) continue;
            for (int j = 0; j < cnt[i]; j++) {
                if (i - 1 <= k) {
                    ans += i;
                    k -= i - 1;
                } else {
                    ans += k;
                    k = 0;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
