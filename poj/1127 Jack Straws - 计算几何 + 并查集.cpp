#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define eps 1e-8
#define maxn 20
int n;
int fa[maxn];
struct Point {//µã
    double x, y;
    Point() { }
    Point(double a, double b) {
        x = a, y = b;
    }
};
struct Line {//Ïß
    Point a, b;
    Line() { }
    Line(Point x, Point y) {
        a = x, b = y;
    }
}l[maxn];
void init() {
    for(int i = 0; i < maxn; i++) fa[i] = i;
}
int find(int x) {
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
inline int sig(double k) {
    return k < -eps ? -1 : k > eps;
}
inline double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}
inline double xmult(Point a, Point b, Point c) {
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}
inline double dotdet(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}
inline double dot(Point a, Point b, Point c) {
    return dotdet(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}
inline int between(Point a, Point b, Point c) {
    return sig(dot(a, b, c));
}
inline int intersect(Point a, Point b, Point c, Point d, Point &p) {
    double s1, s2, s3, s4;
    int d1 = sig(s1 = xmult(a, b, c));
    int d2 = sig(s2 = xmult(a, b, d));
    int d3 = sig(s3 = xmult(c, d, a));
    int d4 = sig(s4 = xmult(c, d, b));
    if ((d1^d2) == -2 && (d3^d4) == -2) {
        p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
        p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
        return 1;
    }
    if (d1 == 0 && between(c, a, b) <= 0) return 2;
    if (d2 == 0 && between(d, a, b) <= 0) return 2;
    if (d3 == 0 && between(a, c, d) <= 0) return 2;
    if (d4 == 0 && between(b, c, d) <= 0) return 2;
    return 0;
}
inline int intersect(Line u, Line v, Point &p) {
    return intersect(u.a, u.b, v.a, v.b, p);
}

int main() {
    while(~scanf("%d", &n)) {
        if(!n) break;
        init();
        Point a, b, c;
        double x1, x2, y1, y2;
        for(int i = 1; i <= n; i++) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a = Point(x1, y1);
            b = Point(x2, y2);
            l[i] = Line(a, b);
            for(int j = 1; j < i; j++) {
                if(intersect(l[i], l[j], c) != 0) {
                    int aa = find(i), bb = find(j);
                    if(aa != bb) fa[aa] = bb;
                }
            }
        }
        int q1, q2;
        while(1) {
            scanf("%d%d", &q1, &q2);
            if(!q1 && !q2) break;
            else {
                q1 = find(q1), q2 = find(q2);
                if(q1 == q2) printf("CONNECTED\n");
                else printf("NOT CONNECTED\n");
            }
        }
    }
    return 0;
}
