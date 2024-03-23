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

const int N = 22;
const int L = 1000;
int pos[N];
int v[N];
int n, T;
int cnt[N];
bool meet(int a, int b) {
    if((v[a] > 0 && v[b] > 0) || (v[a] < 0 && v[b] < 0)) return false;
    bool visit[1000];
    memset(visit, false, sizeof(visit));
    int step = v[a] > 0 ? 1 : -1;
    visit[pos[a]] = true;
    visit[pos[b]] = true;
    int tmp = pos[a];
    step = v[a] > 0 ? 1 : -1;
    for(int i = 1; i <= abs(v[a]); i++) {
        tmp = (tmp + step + L) % L;
        visit[tmp] = true;
    }
    tmp = pos[b];
    step = v[b] > 0 ? 1 : -1;
    for(int i = 1; i <= abs(v[b]); i++) {
        tmp = (tmp + step + L) % L;
        if(visit[tmp]) {
            cnt[a]++;
            cnt[b]++;
            return true;
        }
    }
    return false;
}

int main() {
    while(cin >> n >> T) {
        for(int i = 0; i < n; i++) cin >> pos[i];
        for(int i = 0; i < n; i++) cin >> v[i];
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= T; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = j + 1; k < n; k++) {
                    meet(j, k);
                }
            }
            for(int j = 0; j < n; j++) pos[j] = (pos[j] + v[j] + L) % L;
        }
        for(int i = 0; i < n; i++)
            cout << cnt[i] << " ";
        cout << endl;
    }
    return 0;
}
