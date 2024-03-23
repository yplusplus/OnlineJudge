#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define eps 1e-10
double H, h, D;
double calc(double x) {
	double y = (D * h - H * x) / (D - x);
	return y + x;
}

void solve() {
	double low, high, mid, mmid, ans;
	low = 0.0, high = h * D / H;
	while(low + eps < high) {
		mid = (low + high) / 2.0;
		mmid = (mid + high) / 2.0;
		double mid_s = calc(mid), mmid_s = calc(mmid);
		if(mid_s < mmid_s) ans = mmid_s, low = mid;
		else ans = mid_s, high = mmid;
	}
	printf("%.3f\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lf%lf%lf", &H, &h, &D);
		solve();
	}
	return 0;
}