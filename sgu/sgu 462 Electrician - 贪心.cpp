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
const int N = 33333;
int fa[N], n;
vector<int> vec;

//贪心
//假如每条边的r都不一样，那么无论顺序怎样都不会影响最后答案
//所以只需要考虑r相同的边，由于r相同的时候如果成环是要删最早放入的边
//那么很容易得到一种不会更差的顺序，就是r相同的时候p小的优先放
//但是考虑代码的实现，我反过来排序，既如果r相同p大的优先，否则r大的优先
//这样只需要一个并查集就可以很方便的得到答案，当加入一条边成环的时候是必须删去这条边的，很容易证明
//输出方案时逆序输出即可

struct Wire {
    int a, b, r, p, id;
    Wire(){}
    Wire(int _a, int _b, int _r, int _p, int _id) {
        a = _a, b = _b, r = _r, p = _p, id = _id;
    }
    bool operator< (const Wire &x) const {
        if(r == x.r) return p > x.p;
        else return r > x.r;
    }
}wire[N];

int bs(int x) {
    int l = 0, r = vec.size() - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(vec[mid] == x) return mid;
        else if(vec[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

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
        vec.clear();
        for(int i = 0; i < n; i++) {
            int a, b, r, p;
            cin >> a >> b >> r >> p;
            wire[i] = Wire(a, b, r, p, i + 1);
            vec.pb(a);
            vec.pb(b);
        }
        sort(wire, wire + n);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for(int i = 0; i < vec.size(); i++) fa[i] = i;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int a = bs(wire[i].a);
            int b = bs(wire[i].b);
            if(Union(a, b)) ans += wire[i].p;
        }
        cout << ans << endl;
        for(int i = n - 1; i >= 0; i--) {
            printf("%d%c", wire[i].id, i == 0 ? '\n' : ' ');
        }
    }
    return 0;
}
