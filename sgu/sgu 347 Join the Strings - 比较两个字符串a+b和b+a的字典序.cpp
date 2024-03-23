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
string str[N];
int n;

bool cmp(const string &a, const string &b) {
    string ab = a + b;
    string ba = b + a;
    return ab < ba;
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n; i++) cin >> str[i];
        sort(str, str + n, cmp);
        for(int i = 0; i < n; i++) {
            cout << str[i];
        }
        puts("");
    }
    return 0;
}
