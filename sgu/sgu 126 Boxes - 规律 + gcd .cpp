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

int A, B;
//����ˮ��
//����Ӧ�������gcd(A, B)��Ȼ��tmp = (A + B) / gcd(A, B);
//���tmp == 2 ^ k
//ans��Ϊk��������
//����������ô�Ƴ�����
int main() {
    while(cin >> A >> B) {
        if(A == 0 || B == 0) {
            cout << 0 << endl;
            continue;
        }
        if((A + B) & 1) {
            cout << -1 << endl;
            continue;
        }
        int ans = 0;
        while(1) {
            if(A > B) swap(A, B);
            if(A == 0) break;
            B -= A;
            A *= 2;
            ans++;
            if(ans >= 10000000) {
                ans = -1;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
