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
const int N = 11;
int n, m;
int a[N][111];
vector<int> query;
vector<int> vec[N];
void check() {
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        bool found = false;
        for(int j = 0; j < query.size(); j++) {
            if(query[j] < 0) {
                if(a[i][-query[j]]) found = true;
            } else {
                if(!a[i][query[j]]) found = true;
            }
        }
        if(!found) ans.pb(i);
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) {
        cout << vec[ans[i]].size();
        for(int j = 0; j < vec[ans[i]].size(); j++) cout << " " << vec[ans[i]][j];
        cout << endl;
    }
}

int main() {
    int size, x;
    while(cin >> n >> m) {
        memset(a, false, sizeof(a));
        for(int i = 0; i < n; i++) {
            vec[i].clear();
            cin >> size;
            while(size--) {
                cin >> x;
                vec[i].pb(x);
                a[i][x] = true;
            }
        }
        while(m--) {
            query.clear();
            cin >> size;
            while(size--) {
                cin >> x;
                query.pb(x);
            }
            check();
        }
    }
    return 0;
}
