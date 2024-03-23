#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
int n, m;
int dfs(int m, int n) {
    if(n == 1 || m == 1) return 1;
    if(n > m) return dfs(m, m);
    if(n == m) return dfs(m, n - 1) + 1;
    if(n < m) return dfs(m - n, n) + dfs(m, n - 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &m, &n);
        int ans = dfs(m, n);
        printf("%d\n", ans); 
    }
    return 0;
}
