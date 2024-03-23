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
const int N = 111;
int chain[N];

//贪心，显然如果是1的话，则用来合并两个非1的最优
//对于没有1的情况，一开始单纯以为是直接两两合并
//实际上，每次拆最短链的一个环出来合并当前最长的两条链，这样不会比直接两两合并更差
//而且在拆多次的情况下，可能直接把一条链拆没了，那么相当于少处理一条链（其实就是有1的情况）
//两两合并：每次减少一条链
//拆最短链合并：每次至少减少一条链
int main() {
    int n;
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> chain[i];
        }
        sort(chain, chain + n);
        int ans = 0;
        int l = 0, r = n - 1;
        while(l < r) {
            chain[l]--;
            chain[r-1] += chain[r] + 1;
            r--;
            ans++;
            if(chain[l] == 0) l++;
        }
        cout << ans << endl;
    }
    return 0;
}
