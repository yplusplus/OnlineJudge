#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

long long sq(long long x) { return x * x; }
const int N = 2 * 111111;
int n, m;
int x1, y1, x2, y2;
int ans[N];
vector<long long> number;

struct Point {
    long long x, y, qid;
    Point() {}
    void read(int _qid) { scanf("%lld%lld", &x, &y); x *= x, y *= y; qid = _qid; }
    Point(long long x, long long y) : x(x), y(y) {}
    long long distFrom(const Point &p) { return sq(x - p.x) + sq(y - p.y); }
    bool operator<(const Point &p) const { return x >= p.x; }
} point[N], query[N];

struct BIT {
    int c[N];
    void clear() { memset(c, 0, sizeof(c)); }
    int lowbit(int x) { return x & (-x); }
    void add(int x, int v) { for (int i = x; i < N; i += lowbit(i)) c[i] += v; }
    int query(int x) { int res = 0; for (int i = x; i; i -= lowbit(i)) res += c[i]; return res; }
} bit;

int main() {
    while (~scanf("%d%d%d%d", &x1, &y1, &x2, &y2)) {
        Point A(x1, y1), B(x2, y2);
        scanf("%d", &n);
        number.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x1, &y1);
            Point p(x1, y1);
            point[i] = Point(p.distFrom(A), p.distFrom(B));
            number.push_back(point[i].y);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) { 
            query[i].read(i); 
            number.push_back(query[i].y);
        }
        sort(number.begin(), number.end());
        number.erase(unique(number.begin(), number.end()), number.end());
        sort(point, point + n);
        sort(query, query + m);
        bit.clear();
        for (int i = 0, j = 0; i < m; i++) {
            while (j < n && point[j] < query[i]) {
                int pos = lower_bound(number.begin(), number.end(), point[j].y) - number.begin() + 1;
                bit.add(pos, 1);
                j++;
            }
            int pos = lower_bound(number.begin(), number.end(), query[i].y) - number.begin() + 1;
            ans[query[i].qid] = j - bit.query(pos - 1);
            //cout << query[i].qid << " " << query[i].x << " " << query[i].y << endl;
        }
        for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
