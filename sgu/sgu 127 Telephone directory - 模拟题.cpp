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

const int N = 8888;
int k, n;
int number[N];
int main() {
    while(cin >> k >> n) {
        for(int i = 0; i < n; i++) cin >> number[i];
        sort(number, number + n);
        int pageCnt = 2;
        int curPage = 0;
        int pre = -1;
        for(int i = 0; i < n; i++) {
            if(curPage == k || number[i] / 1000 != pre) {
                pageCnt++;
                curPage = 1;
                pre = number[i] / 1000;
            } else {
                curPage++;
            }
        }
        cout << pageCnt << endl;
    }
    return 0;
}
