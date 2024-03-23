#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int K = 110;
const int N = 110;
int n, k, t;
int dp[N];

struct Gangster {
    int a, b, c;
    bool operator< (const Gangster &x) const {
        return a < x.a;
    }
} gangster[N];

int main() {
    scanf("%d%d%d", &n, &k, &t);
    for (int i = 1; i <= n; i++) { scanf("%d", &gangster[i].a); }
    for (int i = 1; i <= n; i++) { scanf("%d", &gangster[i].c); }
    for (int i = 1; i <= n; i++) { scanf("%d", &gangster[i].b); }
    sort(gangster + 1, gangster + n + 1);
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] != -1 && abs(gangster[i].a - gangster[j].a) >= abs(gangster[i].b - gangster[j].b)) dp[i] = max(dp[i], dp[j] + gangster[i].c);
        }
    }
    int ans = *max_element(dp, dp + 1 + n);
    printf("%d\n", ans);
    return 0;
}
