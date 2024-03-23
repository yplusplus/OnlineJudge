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
const int N = 111111;
int a[N], c[N];
vector<int> vec;
int n, x;

//����ÿ��������ͳһ��ȥa��Ȼ����ǰ׺��sum[]
//�������(a,b]�����������ȼ���sum[b] - sum[a] > 0����sum[b] > sum[a]
//����ת��Ϊ��ÿ����ǰ���ж��ٸ�����С������bit ���� segmentTree~
//ע��Ҫ����һ�����ʾȡ������ǰ׺��

void update(int x, int v) {
    for (int i = x; i < n; i += lowbit(i)) {
        c[i] += v;
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += c[i];
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    a[0] = 0;
    while (T--) {
        scanf("%d%d", &n, &x);
        vec.clear();
        memset(c, 0, sizeof(c));
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            a[i] += a[i - 1] - x;
            vec.pb(a[i]);
            if (a[i] > 0) ans++;
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for (int i = 1; i <= n; i++) {
            int id = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
            ans += sum(id - 1);
            update(id, 1);
        }
        cout << ans << endl;
    }
    return 0;
}
