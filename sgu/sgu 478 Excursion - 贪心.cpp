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
int num[N];
pii p[N];
int a, b;
int n;
//贪心
//每次调整后要保证剩下可调整人数最多
//所以
//如果这次人数比上次多，那么增加男生
//如果这次人数比上次少，那么减少女生
//如果相等则不用处理

bool solve() {
    int boys = a;
    int girls = b;
    num[0] = b;
    for(int i = 1; i <= n; i++) {
        if(num[i] > num[i-1]) {
            if(num[i] - num[i-1] > boys) return false;
            else {
                p[i] = mp(num[i] - num[i-1], 0);
                boys -= num[i] - num[i-1];
            }
        } else if(num[i] < num[i-1]) {
            if(num[i-1] - num[i] > girls) return false;
            else {
                p[i] = mp(0, num[i-1] - num[i]);
                girls -= num[i-1] - num[i];
            }
        } else p[i] = mp(0, 0);
    }
    return true;
}

int main() {
    while(cin >> a >> b) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> num[i];
        }
        if(solve()) {
            for(int i = 1; i <= n; i++) {
                cout << p[i].fi << " " << p[i].se << endl;
            }
        } else puts("ERROR");
    }
    return 0;
}
