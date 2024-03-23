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
const int N = 15555;
int w[N], l[N], pain[N];
bool visit[N];
int n;
pii a[N];
//���⣡������
//�տ�ʼ������̰�ģ����˺ö��춼�㲻����@#��%��#@��������&@#��%
//����õ�N���ˮ���ߣ�һ������ѡ��һ��p��������ˮ����������ˮ����
//��ô�ֶ���ˮ������ֱ������ȥ��ˮһ��һ������ȥ�����տ��ܵ���ĳһ��
//�ܹ���������ܶ����������ˮ����ʱ����һ��һ��Ҫ�ֶ���ˮ��
//������һ�����ϵ����в������������˷���֮�⣬�����ս��û��ʲôӰ�졣
//���Ǻ����׵õ�һ��O(n*n)���㷨��ö����ߵķ�ˮ�㣬Ȼ��ģ���ˮ���̣�
//���·��ü��ɡ����ǣ���TLE������Ҫ�Ż���������
//��ͼ�Ż��㷨�����ѡ���˵�p���ˮ������������£�����Ҫ�Ե�q���ˮ��ԭ���ǣ�
//w[p] + w[p+1] + ... + w[q-1] + w[q] <= l[q];
//�����ʽ�ӿ��Եõ�һ��̰�����ʣ��������ѡ��p1ʱ��q��Ҫ�ֶ���ˮ����ôѡ��
//p2>p1ʱ��qҲһ��Ҫ�ֶ���ˮ��
//������һ�㣬���Ƕ�ÿ���������һ���ؼ���
//a[i] = w[1] + w[2] + ... + w[i] - l[i];
//���pΪ��һ�㣬��ô��Ҫ�ֶ���ˮ�Ĳ�һ����a[i] <= 0
//����pΪ�ڶ��㣬��ô��Ҫ�ֶ���ˮ�Ĳ�һ����a[i] - w[1] <= 0
//������ƣ����Է������е����Եģ���ô����һ��ʼֻ��Ҫ��a����
//Ȼ��Ϳ�����һ�������ݵ�ָ���ǰ����ɨ�裬�ҵ��µ���Ҫ��ˮ�Ĳ㣬�ۼӼ��ɡ�
//����ʱ�临�Ӷ�ΪO(nlogn)��

int main() {
    while (cin >> n) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> w[i] >> l[i] >> pain[i];
            sum += w[i];
            a[i] = mp(sum - l[i], i);
        }
        sort(a + 1, a + 1 + n);
        memset(visit, false, sizeof(visit));
        int p = 1;
        int delta = 0;
        int ansPain = inf, ansId = -1, tmpPain = 0;
        for (int i = 1; i <= n; i++) {
            while (p <= n && a[p].fi - delta <= 0) {
                visit[a[p].se] = true;
                tmpPain += pain[a[p].se];
                p++;
            }
            if (visit[i-1]) tmpPain -= pain[i-1];
            if (tmpPain < ansPain) {
                ansPain = tmpPain;
                ansId = i;
            }
            delta += w[i];
        }
        for (int i = ansId, tmpW = 0; i <= n; i++) {
            tmpW += w[i];
            if (tmpW <= l[i]) cout << i << endl;
        }
    }
    return 0;
}
