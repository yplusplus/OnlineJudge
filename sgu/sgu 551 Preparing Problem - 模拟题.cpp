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

int main() {
    int n, tA, tB;
    while(cin >> n >> tA >> tB) {
        int aCnt = 0, bCnt = 0;
        int aEnd = 0, bEnd = 0;
        while(1) {
            if(aEnd == bEnd) {
                if(aCnt + bCnt >= n) break;
                aEnd += tA, bEnd += tB;
                aCnt++, bCnt++;
            } else {
                if(aCnt + bCnt - 1 >= n) break;
                if(aEnd > bEnd) {
                    bEnd += tB, bCnt++;
                } else {
                    aEnd += tA, aCnt++;
                }
            }
        }
        cout << aCnt + bCnt << " " << max(aEnd, bEnd) << endl;
    }
    return 0;
}
