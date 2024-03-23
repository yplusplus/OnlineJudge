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
const int N = 444444;
map<pii, int> hash;
int ans, n;
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[a] = b;
    return true;
}

int main() {
    while(cin >> n) {
        for(int i = 1; i <= (n << 1); i++) {
            fa[i] = i;
        }
        hash.clear();
        int a, b, tot = 0;
        ans = 0;
        bool found = false;
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            if(!hash[mp(x, y)]) {
                hash[mp(x, y)] = ++tot;
            }
            a = hash[mp(x, y)];
            cin >> x >> y;
            if(!hash[mp(x, y)]) {
                hash[mp(x, y)] = ++tot;
            }
            b = hash[mp(x, y)];
            if(!Union(a, b) && !found) {
                found = true;
                ans = i + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
