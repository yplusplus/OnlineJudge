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
string s, t;
vector<char> vec;

//贪心
//用栈实现比较方便
//坑爹的题意！！！！！！
//转换规则：
//a->B
//b->A
//a->Aba
//b->Bab

bool solve() {
    vec.clear();
    vec.pb(s[0]);
    for(int i = 0; i < t.length(); i++) {
        if(vec.empty()) return false;
        if(vec.back() == t[i]) {
            vec.pb('A' + 'B' - vec.back());
        } else vec.pop_back();
    }
    return vec.empty();
}

int main() {
    while(cin >> s >> t) {
        puts(solve() ? "YES" : "NO");
    }
    return 0;
}
