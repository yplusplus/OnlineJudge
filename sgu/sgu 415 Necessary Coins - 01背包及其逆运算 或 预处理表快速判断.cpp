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
const int N = 222;
int a[N];
int n, x;

//ֱ�ӱ���O(n*n*m)
void solve1() {
    sort(a, a + n);
    bool visit[11111];
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        memset(visit, false, sizeof(visit));
        visit[0] = true;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            for(int k = x; k >= 0; k--) {
                if(visit[k] && k + a[j] <= x) visit[k + a[j]] = true;
            }
        }
        if(!visit[x]) ans.pb(a[i]);
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) {
        printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
}
//01��������������O(n*m)
void solve2() {
    int f[11111], g[11111];
    //f[i] ��ʾ��a[1-n]���i������ж�����
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for(int i = 0; i < n; i++)
        for(int j = x; j >= a[i]; j--)
            f[j] += f[j - a[i]];
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        //g[j] ��ʾ��a[1-n]�г���a[i]���j������ж�����
        memset(g, 0, sizeof(g));
        for(int j = 0; j <= x; j++) {
            if(j < a[i]) g[j] = f[j];
            else g[j] = f[j] - g[j-a[i]];
        }
        if(g[x] == 0) ans.pb(a[i]);
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) {
        printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
}
//����һ������ O(n*m) �ǶԱ���������һ���Ż�
//O(n*m)Ԥ�����L[i], R[i]
//L[i] ��ʾ��a[1~(i-1)] ������ɵ���
//R[i] ��ʾ��a[i~n] ������ɵ���
//����ÿ��a[i], ��ʵֻҪ�����i-1�����ܹ��ɵļ���,��(i+1~n)�����ܹ��ɵļ���
//ö��j���ж�j��x-j�Ƿ�����������������
int main() {
    while(cin >> n >> x) {
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        //solve1();
        solve2();
    }
    return 0;
}
