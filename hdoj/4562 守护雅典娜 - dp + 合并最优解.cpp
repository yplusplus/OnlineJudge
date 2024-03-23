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

const int N = 1111;
int getDist(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

struct Circle {
    int x, y;
    int r;
    Circle() {}
    Circle(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
    bool operator<(const Circle &circle) const {
        return r < circle.r;
    }
    bool contains(const Circle &circle) const {
        if (r <= circle.r) return false;
        return (r - circle.r) * (r - circle.r) > getDist(x, y, circle.x, circle.y);
    }
    bool contains(int _x, int _y) const {
        return r * r > getDist(x, y, _x, _y);
    }
    bool intersect(const Circle &circle) const {
        int dist = getDist(x, y, circle.x, circle.y);
        return (r + circle.r) * (r + circle.r) >= dist && (r - circle.r) * (r - circle.r) <= dist;
    }
    bool isOnTheEdgeByPoint(int _x, int _y) {
        return r * r == getDist(x, y, _x, _y);
    }
} circle[N];

int X, Y, n;
int dp[N][2];
int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> X >> Y;
        for (int i = 0; i < n; i++) {
            int x, y, r;
            cin >> x >> y >> r;
            circle[i] = Circle(x, y, r);
        }
        vector<Circle> vec[2];
        for (int i = 0; i < n; i++) {
            bool a = circle[i].contains(0, 0);
            bool b = circle[i].contains(X, Y);
            if (!circle[i].isOnTheEdgeByPoint(0, 0) && !circle[i].isOnTheEdgeByPoint(X, Y) && (a ^ b)) {
                vec[a ? 0 : 1].pb(circle[i]);
            }
        }
        memset(dp, 0, sizeof(dp));
        sort(vec[0].begin(), vec[0].end());
        sort(vec[1].begin(), vec[1].end());
        int ans = 0;
        for (int i = 0; i < vec[0].size(); i++) {
            dp[i][0] = 1;
            for (int j = 0; j < i; j++) {
                if (vec[0][i].contains(vec[0][j])) dp[i][0] = max(dp[i][0], dp[j][0] + 1);
            }
            ans = max(ans, dp[i][0]);
        }
        for (int i = 0; i < vec[1].size(); i++) {
            dp[i][1] = 1;
            for (int j = 0; j < i; j++) {
                if (vec[1][i].contains(vec[1][j])) dp[i][1] = max(dp[i][1], dp[j][1] + 1);
            }
            ans = max(ans, dp[i][1]);
        }
        for (int i = 0; i < vec[0].size(); i++) {
            for (int j = 0; j < vec[1].size(); j++) {
                if (!vec[0][i].intersect(vec[1][j])) ans = max(ans, dp[i][0] + dp[j][1]);
            }
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
