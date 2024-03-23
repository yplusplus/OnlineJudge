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
const int H = 10010;
vector<int> vec;
bool visit[H];
int sg[H];
int k, m;
int main() {
    while (scanf("%d", &k), k) {
        vec.resize(k);
        //int maxH = 0;
        for (int i = 0; i < k; i++) {
            scanf("%d", &vec[i]);
        }
        sg[0] = 0;
        for (int i = 1; i < H; i++) {
            memset(visit, false, sizeof(visit));
            int j;
            for (j = 0; j < k; j++) if (i >= vec[j]) visit[sg[i - vec[j]]] = true;
            j = 0;
            while (visit[j]) j++;
            sg[i] = j;
        }
        scanf("%d", &m);
        char str[111];
        for (int i = 0; i < m; i++) {
            int cnt, x;
            int ans = 0;
            scanf("%d", &cnt);
            for (int j = 0; j < cnt; j++) {
                scanf("%d", &x);
                ans ^= sg[x];
            }
            str[i] = ans ? 'W' : 'L';
        }
        str[m] = 0;
        puts(str);

    }
    return 0;
}
