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

const int N = 55;
vector<int> vec[N];
bool visit[N];
int n, x;

int main() {
    while(cin >> n >> x) {
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 1; i <= n; i++) {
            int d, a;
            cin >> d;
            while(d--) {
                cin >> a;
                vec[i].pb(a);
                vec[a].pb(i);
            }
        }
        memset(visit, false, sizeof(visit));
        for(int i = 0; i < vec[x].size(); i++) {
            int v = vec[x][i];
            for(int j = 0; j < vec[v].size(); j++) {
                visit[vec[v][j]] = true;
            }
        }
        for(int i = 0; i < vec[x].size(); i++) {
            visit[vec[x][i]] = false;
        }
        visit[x] = false;

        vector<int> scheme;
        for(int i = 1; i <= n; i++) {
            if(visit[i]) scheme.pb(i);
        }
        cout << scheme.size() << endl;
        for(int i = 0; i < scheme.size(); i++) {
            printf("%d%c", scheme[i], i == scheme.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
