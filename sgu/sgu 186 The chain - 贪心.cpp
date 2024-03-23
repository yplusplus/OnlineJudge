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
const int N = 111;
int chain[N];

//̰�ģ���Ȼ�����1�Ļ����������ϲ�������1������
//����û��1�������һ��ʼ������Ϊ��ֱ�������ϲ�
//ʵ���ϣ�ÿ�β��������һ���������ϲ���ǰ��������������������ֱ�������ϲ�����
//�����ڲ��ε�����£�����ֱ�Ӱ�һ������û�ˣ���ô�൱���ٴ���һ��������ʵ������1�������
//�����ϲ���ÿ�μ���һ����
//��������ϲ���ÿ�����ټ���һ����
int main() {
    int n;
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> chain[i];
        }
        sort(chain, chain + n);
        int ans = 0;
        int l = 0, r = n - 1;
        while(l < r) {
            chain[l]--;
            chain[r-1] += chain[r] + 1;
            r--;
            ans++;
            if(chain[l] == 0) l++;
        }
        cout << ans << endl;
    }
    return 0;
}
