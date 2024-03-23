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
bool isSelfNumber[64];
int n, k, p;
pii q[5555];
//d(n) < 64
//¹ö¶¯Êý×é
int calc(int x) {
    int res = x;
    while(x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

bool cmp(const pii &a, const pii &b) {
    return a.se < b.se;
}

int main() {
    while(cin >> n >> k) {
        for(int i = 0, x; i < k; i++) {
            cin >> x;
            q[i] = mp(x, i);
        }
        sort(q, q + k);
        memset(isSelfNumber, true, sizeof(isSelfNumber));
        int p1 = 0, p2 = 0;
        for(int i = 1; i <= n; i++) {
            if(isSelfNumber[i&63]) {
                p1++;
                while(p1 == q[p2].fi) {
                    q[p2].fi = i;
                    p2++;
                }
            }
            int rec = calc(i);
            isSelfNumber[rec&63] = false;
            isSelfNumber[i&63] = true;
        }
        sort(q, q + k, cmp);
        cout << p1 << endl;
        for(int i = 0; i < k; i++) {
            printf("%d%c", q[i].fi, i == k - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
