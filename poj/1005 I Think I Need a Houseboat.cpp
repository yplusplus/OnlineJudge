#include "iostream"
using namespace std;
const double pi = 3.1415926;
int main() {
	double x, y;
	int t = 1, nt;
	cin >> nt;
	while(t <= nt) {
		scanf("%lf%lf", &x, &y);
		double area = (x * x + y * y) * pi / 2;
		int year = (int)(area / 50) + 1;
		printf("Property %d: This property will begin eroding in year %d.\n", t++, year);
	}
	printf("END OF OUTPUT.\n");
	return 0;
}