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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

int n, m;
bool visit[10010];
int a[110];
int main() {
    int Case = 1;
    while(cin >> n >> m) {
        if(!n && !m) break;
        memset(visit, false, sof(visit));
        int minn = 10010, maxx = 0;
        int ans = 0;
        int nn = n * m;
        for(int i = 1; i <= m; i++) {
            cin >> a[i];
            visit[a[i]] = 1;
        }
        for(int i = 1; i <= nn; i++) {
            if(!visit[i]) {
                minn = min(minn, i);
                maxx = max(maxx, i); 
            }
        }
        sort(a + 1, a + 1+ m);
        for(int i = m; i; i--) {
            int tmp = a[i];
                int cnt = 0;
            if(maxx < a[i]) {
                ans++;
                while(cnt < 3) {
                    if(!visit[minn+1]) cnt++;
                    minn++;
                }
            } else {
                while(visit[--maxx]);
                while(cnt < 2) {
                    if(!visit[minn+1]) cnt++;
                    minn++;
                }
            }
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
