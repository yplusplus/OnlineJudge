#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 10500
#define eps 1e-8
#define pi 3.1415926535897932384626433832795
int n;
double rr;
struct Point {
	double x, y, r, z;
	Point(){}
	Point(double _x, double _y, double _z) {
		x = _x, y = _y, z = _z, r = sqrt(_x * _x + _y * _y) ;
	}
}point[maxn];

double work(double h) {
	double tmp;
	rr = 0.0;
	for(int i = 0; i < n; i++) {
		double r = point[i].r, z = point[i].z;
		double tmp = h * r / (h - z);
		rr = max(rr, tmp);
	}
	double area = pi * rr * rr * h / 3.0;
	return area;
}

void solve(double res) {
	double low = res, high = 10000000, mid, mmid, ansh, ansr;
	while(low + eps < high) {
		mid = (low + high) / 2.0;
		mmid = (mid + high) / 2.0;
		if(work(mid) < work(mmid)) {
			high = mmid;
			ansh = mid;
		} else {
			low = mid;
			ansh = mmid;
		}
		ansr = rr;
	}
	printf("%.3f %.3f\n", ansh, ansr);

}

int main() {
	int T;
	double x, y, z;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		double low = 0.0;
		for(int i = 0; i < n; i++) {
			scanf("%lf%lf%lf", &x, &y, &z);
			point[i] = Point(x, y, z);
			low = max(low, z);
		}
		solve(low);
	}
	return 0;
}