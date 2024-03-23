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
const int N = 11111;
string s;
int n;
int cnt[N];

//有点贪心的感觉，从右往左找到第一个可以变成右括号的左括号
//然后改变这个括号，剩下的变成(((...())...)))即可

int main() {
    while (cin >> s) {
        n = s.length();
        cnt[0] = 1;
        for (int i = 1; i < n; i++) {
            cnt[i] = cnt[i-1] + (s[i] == '(' ? 1 : -1);
        }
        int start = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (cnt[i] > 1 && s[i] == '(') {
                start = i;
                break;
            }
        }
        if (start == -1) {
            puts("No solution");
        } else {
            int tmp = -1;
            for (int i = start; i < n; i++) {
                tmp += s[i] == ')';
            }
            string ans = s.substr(0, start);
            ans += ')';
            ans += string(n - start - 1 - tmp, '(');
            ans += string(tmp, ')');
            cout << ans << endl;
        }
    }
    return 0;
}
