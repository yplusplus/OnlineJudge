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

//判断A的质因子是否都存在与B中
ll gcd(ll a, ll b) {
    return (a % b == 0) ? b : gcd(b, a % b);
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    ll a, b, c;
    while(T--) {
        scanf("%I64d%I64d", &a, &b);
        do {
            c = gcd(a, b);
            a /= c;
        }while(c != 1);
        printf("Case #%d: ", Case++);
        if(a == 1) puts("YES");
        else puts("NO");
    }
    return 0;
}
