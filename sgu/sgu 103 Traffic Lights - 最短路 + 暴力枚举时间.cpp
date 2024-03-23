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
const int N = 333;
int s, t;
int n, m;
int dist[N], pre[N];
bool visit[N];
vector<pii> vec[N];
int initColor[N], remain[N], ti[N][3];
//0 for B
//1 for P
//因为每种灯持续的时间最多100，所以直接暴力判断即可
int calc(int i, int T) {
    if(T <= remain[i]) return initColor[i];
    T -= remain[i];
    int curColor = !initColor[i];
    while(T > ti[i][2]) T -= ti[i][2];
    return (T <= ti[i][curColor]) ? curColor : !curColor;
}

bool spfa(int s, int t) {
    dist[s] = 1;
    memset(visit, false, sizeof(visit));
    memset(pre, -1, sizeof(pre));
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].fi, w = vec[u][i].se;
            for(int j = 0; j <= 500; j++) {
                if(calc(u, dist[u] + j) == calc(v, dist[u] + j)) {
                    int tmp = dist[u] + j + w;
                    if(tmp < dist[v]) {
                        dist[v] = tmp;
                        pre[v] = u;
                        if(!visit[v]) {
                            que.push(v);
                            visit[v] = true;
                        }
                    }
                    break;
                }
            }
        }
    }
    return dist[t] != inf;
}

int main() {
    while(cin >> s >> t) {
        cin >> n >> m;
        string str;
        for(int i = 1; i <= n; i++) {
            vec[i].clear();
            dist[i] = inf;
            cin >> str >> remain[i] >> ti[i][0] >> ti[i][1];
            ti[i][2] = ti[i][0] + ti[i][1];
            initColor[i] = (str == "P");
        }
        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            vec[a].pb(mp(b, c));
            vec[b].pb(mp(a, c));
        }
        if(spfa(s, t)) {
            cout << dist[t] - 1 << endl;
            int x = t;
            vector<int> scheme;
            while(x != -1) {
                scheme.pb(x);
                x = pre[x];
            }
            reverse(scheme.begin(), scheme.end());
            for(int i = 0; i < scheme.size(); i++) {
                printf("%d%c", scheme[i], i == scheme.size() - 1 ? '\n' : ' ');
            }
        } else cout << 0 << endl;
    }
    return 0;
}
