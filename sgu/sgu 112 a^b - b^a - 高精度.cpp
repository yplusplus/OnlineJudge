#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 510
int c[maxn+10], d[maxn+10];
int a, b, l1, l2;
int calc(int a, int b, int c[]) {
    for(int i = 0; i < maxn; i++) c[i] = 0;
    c[0] = a;
    while(--b) {
        for(int i = 0; i < maxn; i++) c[i] *= a;
        for(int i = 0; i < maxn; i++)
            if(c[i] >= 10) c[i+1] += c[i] / 10, c[i] %= 10;
    }
    for(int i = maxn; i >= 0; i--)
        if(c[i] != 0) return i;
}

int Minus() {
    for(int i = 0; i <= l1; i++) {
        if(c[i] >= d[i]) c[i] -= d[i];
        else c[i] = c[i] - d[i] + 10, c[i+1]--;
    }
    for(int i = maxn; i >= 0; i--)
        if(c[i] != 0) return i;
}

int check() {
    if(l1 > l2) return 1;
    else if(l1 < l2) return -1;
    else {
        for(int i = l1; i >= 0; i--)
            if(c[i] > d[i]) return 1;
            else if(c[i] < d[i]) return -1;
        return 0;
    }
}

int main() {
    while(~scanf("%d%d", &a, &b)) {
        l1 = calc(a, b, c);
        l2 = calc(b, a, d);
        int flag = check();
        if(flag == 0) {
            printf("0\n");
        } else if(flag == 1) {
            int l = Minus();
            for(int i = l; i >= 0; i--) printf("%d", c[i]);
            printf("\n");
        } else {
            printf("-");
            for(int i = 0; i < maxn; i++) swap(c[i], d[i]);
            swap(l1, l2);
            int l = Minus();
            for(int i = l; i >= 0; i--) printf("%d", c[i]);
            printf("\n");
        }
    }
    return 0;
}
