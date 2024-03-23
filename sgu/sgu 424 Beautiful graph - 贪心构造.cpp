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
int n;

//贪心构造
//乱YY的，居然过了
/*
图形如下：
        o ______
      / | \     \
     o  o  o ... o
      \ | /     /
        o ______
*/
//每多一个点就可以增加两条边
//其实就是尽可能分享少的边，最少就是两条！

int main() {
    while(cin >> n) {
        if(n == 1) {
            cout << 1 << " " << 0 << endl;
        } else if(n == 2) {
            cout << 2 << " " << 1 << endl;
            cout << 1 << " " << 2 << endl;
        } else if(n == 3) {
            cout << 3 << " " << 3 << endl;
            cout << 1 << " " << 2 << endl;
            cout << 2 << " " << 3 << endl;
            cout << 3 << " " << 1 << endl;
        } else {
            cout << n << " " << (n - 2) * 2 << endl;
            cout << 1 << " " << 2 << endl;
            cout << 2 << " " << 3 << endl;
            for(int i = 4; i <= n; i++) {
                cout << i << " " << 1 << endl;
                cout << i << " " << 3 << endl;
            }
        }
    }
    return 0;
}
