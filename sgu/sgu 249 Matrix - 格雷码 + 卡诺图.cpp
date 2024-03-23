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
const int N = 20;
int gray[1<<N];
int n, m;

//突然想到格雷码和卡诺图，然后就没然后了。
int main() {
    for(int mask = 0; mask < (1 << N); mask++) {
        gray[mask] = mask & (1 << N >> 1);
        for(int i = 0; i < N - 1; i++) {
            gray[mask] |= ((mask >> i & 1) ^ (mask >> i >> 1 & 1)) << i;
        }
    }
    while(cin >> n >> m) {
        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < (1 << m); j++) {
                cout << ((gray[i] << m) + gray[j]) << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
