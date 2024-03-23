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
string s[1010];
void dfs(int l, int r, int k) {
    if(l == r) {
        if(k) puts("<li>");
        puts(s[l].substr(k).c_str());
        if(k) puts("</li>");
        return;
    }
    for(int i = l; i <= r; i++) {
        if(s[i][k] != '*' && s[i][k] != '#') {
            dfs(i, i, k);
        } else {
            int cnt = 0;
            for(int j = i + 1; j <= r; j++) {
                if(s[j][k] == s[i][k]) cnt++;
                else break;
            }
            if(cnt == 0) {
                dfs(i, i, k);
            } else {
                if(k) puts("<li>");
                puts(s[i][k] == '*' ? "<ul>" : "<ol>");
                dfs(i, i + cnt, k + 1);
                puts(s[i][k] == '*' ? "</ul>" : "</ol>");
                if(k) puts("</li>");
                i += cnt;
            }
        }
    }
}

int main() {
    int tot = 0;
    while(cin >> s[tot]) tot++;
    dfs(0, tot - 1, 0);
    return 0;
}
