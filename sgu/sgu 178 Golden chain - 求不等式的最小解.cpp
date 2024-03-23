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

ll n;
//���ִ𰸣������Ϊx����ô������x��1��x+1����������
//Ϊ�˾����ܹ����ÿһ��������ô��ǰ�����һ��Ӧ�õ���ǰ�����еĺͼ�һ
//x, x + 1, (x + 1) * 2, (x + 1) * 4 �ȵ�
//�����ҵ������Ƕ���֮�󣬱���̰���ж����ܸ��Ӷ���O(log^2(n))
//��ʵ����ֱ���󲻵�ʽx+(x+1)*(2^(x+1)-1)>=N����С��
//ֱ��ö�ٵĸ��Ӷ���O(logn)�����϶��ֿ�������O(loglogn)
bool check(ll cnt) {
    ll leave = n - cnt;
    ll sum = cnt;
    cnt += 1;
    while(cnt && leave > 0) {
        leave -= sum + 1;
        sum += sum + 1;
        cnt--;
    }
    return leave <= 0;
}

int main() {
    while(cin >> n) {
        ll l = 0, r = n >> 1;
        ll ans = -1;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if(check(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
