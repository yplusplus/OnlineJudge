#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

#define maxn 100
const int inf = 1 << 27;
int maz[maxn][maxn];
int n, m;

int StoerWagner(int n) {//n ÎªµãÊý
    int v[maxn], dist[maxn];
    bool visit[maxn];
    int cut = inf;
    for(int i = 0; i < n; i++) v[i] = i;
    while(n > 1) {
        int k = 1, pre = 0;
        for(int i = 1; i < n; i++) {
            dist[v[i]] = maz[v[0]][v[i]];
            if(dist[v[i]] > dist[v[k]]) k = i;
        }
        memset(visit, false, sizeof(visit));
        visit[v[0]] = true;
        for(int i = 1; i < n; i++) {
            if(i == n - 1) {
                cut = min(cut, dist[v[k]]);
                for(int j = 0; j < n; j++) {
                    maz[v[pre]][v[j]] += maz[v[j]][v[k]];
                    maz[v[j]][v[pre]] += maz[v[j]][v[k]];
                }
                v[k] = v[--n];
            }
            visit[v[k]] = true;
            pre = k, k = -1;
            for(int j = 1; j < n; j++) {
                if(!visit[v[j]]) {
                    dist[v[j]] += maz[v[pre]][v[j]];
                    if(k == -1 || dist[v[k]] < dist[v[j]])
                        k = j;
                }
            }
        }
    }
    return cut;
}

int main() {
    int T;
    while(scanf("%d", &T), T) {
        while(T--) {
            scanf("%d%d", &n, &m);
            memset(maz, 0, sizeof(maz));
            int sum = 0;
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++) {
                    scanf("%d", &maz[i][j]);
                    sum += maz[i][j];
                }
            int ans = sum - 4 * StoerWagner(n);
            cout << ans << endl;
        }
    }
    return 0;
}

