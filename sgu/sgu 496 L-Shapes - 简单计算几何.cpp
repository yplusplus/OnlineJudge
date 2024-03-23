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
const int N = 5555;

int getDist(pii a, pii b) {
    return (a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se);
}

struct Line {
    pii a, b;
    int len;
    Line(){}
    Line(pii _a, pii _b) {
        a = _a, b = _b;
        len = getDist(a, b);
    }
}line[N];
int n;

bool calc(Line a, Line b, pii &c) {
    if(a.a == b.a || a.a == b.b) {
        c = a.a;
        return true;
    } else if(a.b == b.a || a.b == b.b) {
        c = a.b;
        return true;
    } return false;
}

bool check(Line a, Line b) {
    pii c;
    if(!calc(a, b, c)) return false;
    pii p1, p2;
    p1 = a.a == c ? a.b : a.a;
    p2 = b.a == c ? b.b : b.a;
    if(a.len + b.len == getDist(p1, p2)) return true;
    return false;
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            line[i] = Line(mp(x1, y1), mp(x2, y2));
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(check(line[i], line[j])) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
