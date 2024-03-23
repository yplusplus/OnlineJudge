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
#define MAX 1010
int n;
int fac[10];
bool dp[MAX];
int main() {
    fac[0] = 1;
    for(int i = 1; i < 10; i++) fac[i] = fac[i-1] * 2;
    memset(dp, false, sizeof(dp));
    for(int i = 0; i <= MAX; i++) {
        for(int j = 0; j < 10; j++) {
            if(i + fac[j] < MAX) dp[i+fac[j]] |= !dp[i];
        }
    }
    while(cin >> n) {
        if(dp[n]) puts("Kiki");
        else puts("Cici");
    }
    return 0;
}
