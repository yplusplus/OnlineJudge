#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
int n, m;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &m, &n);
        m = m % n;
        if(m == 0) {
            if(n == 1) printf("NO\n");
            else printf("YES\n");
        } else if(m == 1) printf("NO\n");
        else if(n % m == 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
