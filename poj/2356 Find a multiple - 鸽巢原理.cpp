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
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 10050
int n;
int val[maxn], idx[maxn];
int main() {
    while(~scanf("%d", &n)) {
        int sum = 0;
        int l = -1, r = -1;
        memset(idx, -1, sizeof(idx));
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            sum = (sum + val[i]) % n;
            if(sum == 0) l = 0, r = i;
            else if(idx[sum] == -1) idx[sum] = i;
            else l = idx[sum], r = i;
        }
        if(l != -1) {
            printf("%d\n", r - l);
            for(int i = l + 1; i <= r; i++) 
                printf("%d\n", val[i]);
        } else printf("0\n");
    }
    return 0;
}
