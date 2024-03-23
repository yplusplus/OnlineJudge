#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> Point;
typedef pair<LL, LL> Slope;

#define x first
#define y second

const int N = 555;
Point points[N];

template<typename T>
inline T sqr(T x) {
    return x * x;
}

LL get_dist(const Point &a, const Point &b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

Slope get_slope(const Point &a, const Point &b) {
    LL y = a.y - b.y, x = a.x - b.x;
    LL d = __gcd(x, y);
    return Slope(y / d, x / d);
}

int main() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        map<pair<LL, Slope>, int > count;
        for (int i = 0; i < n; i++) {
            const Point &a = points[i];
            for (int j = i + 1; j < n; j++) {
                const Point &b = points[j];
                Slope slope = get_slope(a, b);
                LL dist = get_dist(a, b);
                count[make_pair(dist, slope)]++;
            }
        }
        int ans = 0;
        for (map<pair<LL, Slope>, int>::iterator it = count.begin(); it != count.end(); it++) {
            ans += it->second * (it->second - 1);
        }
        ans >>= 2;
        cout << ans << endl;
    }
    return 0;
}
