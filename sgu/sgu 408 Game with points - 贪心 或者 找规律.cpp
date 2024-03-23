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

//̰�Ļ���˵�ҹ��ɰ�
//�����׷��ֵ������i(i >= 3)����ʱ��ÿ��������ѡ��Ҫô�Ӵ������룬Ҫô�Ӵ󹲵���߶���
//��Ϊ������ֵ�ĺ���һ���ģ����Ծ���ʹ���ǵĲ��ԽС���Խ��

int main() {
    int n;
    while(cin >> n) {
        double ans = 0;
        if(n == 0) ans = 0;
        else if(n == 1) ans = 1;
        else if(n == 2) ans = 5;
        else {
            ans = 5;
            int maxNumber = 2;
            int maxDistance = 2;
            for(int i = 3; i <= n; i++) {
                if(maxNumber == maxDistance) maxNumber++;
                else maxDistance++;
                ans += maxNumber * maxDistance;
            }
        }
        printf("%.3f\n", ans);
    }
    return 0;
}
