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
const int N = 1000001;
bool isPrime[N];
int Prime[80000], tot;
int n;
void init() {
    memset(isPrime, true, sizeof(isPrime));
    for(ll i = 2; i < N; i++) {
        if(isPrime[i]) {
            Prime[tot++] = i;
            for(ll j = i * i; j < N; j += i) isPrime[j] = false;
        }
    }
}

int main() {
    init();
    while(cin >> n) {
        int ans = 0;
        vector<pii> vec;
        if(n <= 4) {
            cout << 0 << endl;
            continue;
        }
        for(int j = 0; j < tot; j++) {
            int tmp = 2 + Prime[j];
            if(tmp > n) break;
            if(isPrime[tmp]) {
                vec.pb(mp(2, Prime[j]));
            }
        }
        cout << vec.size() << endl;
        for(int i = 0; i < vec.size(); i++) {
            cout << vec[i].fi << " " << vec[i].se << endl;
        }
    }
    return 0;
}
