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
int n, m;

//������
//��ʼһֱ���ǻ�ʣi�����ӵĸ��ʣ�ֻ����O(n^2)��dpȥ���
//ʵ��ÿ����ȥ�ú����Ƕ����¼�����ô��i����������û�б��õ��ĸ����� p = (((n - 1) / n) ^ m).
//����Ϊ���к��Ӷ���ȵģ��������û��ѡ�еĺ����������� p * n
//��ôѡ�к������������� n - p * n
//��Ҫ����˼ά�ˣ�������������

int main() {
    while(cin >> n >> m) {
        double tmp = 1.0 * (n - 1) / n;
        double ans = n;
        for(int i = 0; i < m; i++) {
            ans *= tmp;
        }
        printf("%.10f\n", n - ans);
    }
    return 0;
}
