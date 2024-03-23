#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 50500
#define eps 1e-10
int n;
struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y) {
		x = _x, y = _y;
	}
}point[maxn];

inline double dist(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double work(double x) {
	double maxx = 0.0;
	Point mp = Point(x, 0.0);
	for(int i = 0; i < n; i++) {
		double tmp = dist(mp, point[i]);
		maxx = max(maxx, tmp);
	}
	return maxx;
}

void solve() {
	double ans, x;
	double low = -250000, high = 250000, mid, mmid;
	while(low + eps < high) {
		mid = (low + high) / 2.0;
		mmid = (mid + high) / 2.0;
		double mid_val = work(mid);
		double mmid_val = work(mmid);
		if(mid_val < mmid_val) {
			ans = mid_val, high = mmid, x = mid;
		} else {
			ans = mmid_val, low = mid, x = mmid;
		}
	}
	printf("%.9f %.9f\n", x, sqrt(ans));
}
int main() {
	double x, y;
	while(~scanf("%d", &n)) {
		if(!n) break;
		for(int i = 0; i < n; i++) {
			scanf("%lf%lf", &x, &y);
			point[i] = Point(x, y);
		}
		solve();
	}
	return 0;
}