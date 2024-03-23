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
const double eps = 1e-12;
const ll linf = 1LL << 55;
const int N = 444;
double loc[N];
int n;
double y[N];

//�������뵽���̫�����̫С���ᵼ�´𰸺ܴ�
//Ӧ����һ�������ߣ����ǿ�������������
//���赱ǰ�ļ����dist����һ�������λ����x0
//��ôxi = x0 + i * dist
//res = ��| loc[i] - xi |
//    = ��| loc[i] - x0 - i * dist |
//    = ��| loc[i] - i * dist - x0 |
//    = ��| y[i] - x0 | (y[i] = loc[i] - i * dist)
//��ô���ڵȼ���n���㣬����ֱ���y[i]����һ����x0��ʹ�����е㵽���ľ���֮����С��
//�����Ծ���һ����λ����������x0 = y[n / 2], y[]Ҫ�����򣡣���

double calc(double dist) {
    double res = 0.0;
    for(int i = 0; i < n; i++) {
        y[i] = loc[i] - i * dist;
    }
    sort(y, y + n);
    double first = y[n >> 1];
    for(int i = 0; i < n; i++) {
        res += abs(y[i] - first);
    }
    return res;
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> loc[i];
        }
        double l = 0.0, r = 1e30 + eps;
        for(int i = 0; i < 500; i++) {
            double mid = l + (r - l) / 3.0;
            double mmid = r - (r - l) / 3.0;
            double tmp_mid = calc(mid);
            double tmp_mmid = calc(mmid);
            if(tmp_mid < tmp_mmid) r = mmid;
            else l = mid;
        }
        printf("%.10f\n", calc(l) + eps);
        double first = y[n >> 1];
        for(int i = 0; i < n; i++) {
            printf("%.10f%c", first + i * l, i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
