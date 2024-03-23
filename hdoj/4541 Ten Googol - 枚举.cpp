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

vector<int> vec[15];
string word[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "googol"};
string teen[] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
string shi[] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
void gao() {
    for (int i = 0; i < 9; i++) {
        vec[shi[i].size()].pb((i + 1) * 10);
    }
    for (int i = 0; i < 9; i++) {
        vec[teen[i].size()].pb(11 + i);
    }
    for (int i = 0; i < 10; i++) {
        vec[word[i].size()].pb(i);
    }
    for (int i = 21; i < 100; i++) {
        if (i % 10 == 0) continue;
        int a = i / 10, b = i % 10;
        vec[shi[a - 1].size() + word[b].size()].pb(i);
    }
    for (int i = 0; i < 15; i++) sort(vec[i].begin(), vec[i].end());
}

int main() {
    gao();
    int T, Case = 1;
    cin >> T;
    string googol = string(100, '0');
    while (T--) {
        int n, m;
        cin >> n >> m;
        printf("Case #%d: ", Case++);
        if (n == 9) {
            if (m <= vec[n].size()) cout << vec[n][m-1] << endl;
            else if (m <= vec[n].size() + 4) {
                m -= vec[n].size();
                if (m == 1) cout << 1 << googol << endl;
                else if (m == 2) cout << 2 << googol << endl;
                else if (m == 3) cout << 6 << googol << endl;
                else cout << 10 << googol << endl;
            } else cout << -1 << endl;
        } else {
            if (m <= vec[n].size()) cout << vec[n][m-1] << endl;
            else cout << -1 << endl;
        }
    }
    return 0;
}

