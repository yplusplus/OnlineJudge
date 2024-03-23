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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
int n, m;

//概率题
//开始一直考虑还剩i个盒子的概率，只能用O(n^2)的dp去求解
//实际每个人去拿盒子是独立事件，那么第i个盒子最终没有被拿到的概率是 p = (((n - 1) / n) ^ m).
//又因为所有盒子都相等的，所以最后没被选中的盒子数期望是 p * n
//那么选中盒子数的期望是 n - p * n
//不要惯性思维了！！！！！！！

int main() {
    while(cin >> n >> m) {
        double tmp = 1.0 * (n - 1) / n;
        double ans = n;
        for(int i = 0; i < m; i++) {
            ans *= tmp;
        }
        printf("%.10f\n", n - ans);
    }
    return 0;
}
