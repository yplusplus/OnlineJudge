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

//贪心
//O(n)扫过去，如果当前这个不等，O(n)找到后面第一个和它一样的换过来
//总复杂度O(n^2)

int main() {
    while(cin >> s >> t) {
        int minus = 0;
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == '-') minus++;
            if(t[i] == '-') minus--;
        }
        if(minus != 0 || s.length() != t.length()) {
            puts("-1");
            continue;
        }
        int ans = 0;
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == t[i]) continue;
            else {
                int j;
                for(j = i + 1; j < s.length(); j++) {
                    if(s[j] == t[i]) break;
                }
                swap(s[i], s[j]);
                ans += j - i;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
