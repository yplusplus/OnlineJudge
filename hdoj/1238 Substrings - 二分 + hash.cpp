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
char str[N][N << 1];
int n;
bool check(int mid) {
    //cout << mid << "***********" << endl;
    vector<pair<ull, int> > vec;
    for (int i = 0; i < n; i++) {
        int len = strlen(str[i]);
        //cout << "str " << i << "*********" << endl;
        for (int j = 0; j < len; j++) {
            if (j + mid <= len) {
                ull hashValue = 0;
                for (int k = 0; k < mid; k++) {
                    //cout << str[i][j + k];
                    hashValue = 31 * hashValue + str[i][j + k] - 'a' + 1;
                }
                //cout << endl;
                vec.pb(mp(hashValue, i));
            }
            if (j - mid >= -1) {
                ull hashValue = 0;
                for (int k = 0; k > -mid; k--) {
                    //cout << str[i][j + k];
                    hashValue = 31 * hashValue + str[i][j + k] - 'a' + 1;
                }
                //cout << endl;
                vec.pb(mp(hashValue, i));
            }
        }
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int cnt = 1;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].fi == vec[i-1].fi) cnt++;
        else cnt = 1;
        if (cnt == n) return true;
    }
    return false;
}

int solve(int minLen) {
    int res = 0;
    int l = 1, r = minLen;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int minLen = inf;
        for (int i = 0; i < n; i++) {
            scanf("%s", str[i]);
            minLen = min(minLen, (int)strlen(str[i]));
        }
        printf("%d\n", solve(minLen));
    }
    return 0;
}

