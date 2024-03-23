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
#define maxn 100500
int val[maxn];
int sum[maxn], idx[maxn];
int n, c;

int getint(){
    char c = getchar();
    int t = 0;
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        t = t * 10 + c - '0';
        c = getchar();
    }
    return t;
}

int main() {
    while(~scanf("%d%d", &c, &n)) {
        if(!c && !n) break;
        sum[0] = 0;
        int l, r;
        for(int i = 0; i < maxn; i++) idx[i] = -1;
        for(int i = 1; i <= n; i++) {
            val[i] = getint();
            sum[i] = (sum[i-1] + val[i]) % c;
            if(idx[sum[i]] == -1) idx[sum[i]] = i;
            else l = idx[sum[i]], r = i;
        }
        if(idx[0] != -1) {
            for(int i = 1; i <= idx[0]; i++)
                printf("%d ", i);
            printf("\n");
        } else if(l != - 1) {
            for(int i = l + 1; i <= r; i++) 
                printf("%d ", i);
            printf("\n");
        } else printf("no sweets\n");
        
    }
    return 0;
}
