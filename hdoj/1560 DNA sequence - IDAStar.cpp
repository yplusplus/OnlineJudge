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

const int N = 10;
int n;
char s[N][N];
int end[N], cur[N];
int limit, nextLimit;
char str[N * N];
char ch[] = "ATCG";
int w[256];
bool visit[N];

int cnt[N][N];

int h() {
    int res = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        res = max(res, end[i] - cur[i]);
        for (int j = cur[i]; j < end[i]; j++) {
            cnt[i][w[s[i][j]]]++;
        }
    }
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp = max(tmp, cnt[j][i]);
        }
        ret += tmp;
    }
    return max(ret, res);
}

bool dfs(int dep) {
    int val = h();
    if (val == 0) {
        return true;
    }
    if (dep + val > limit) {
        nextLimit = min(nextLimit, val + dep);
        return false;
    }
    for (int i = 0; i < 4; i++) {
        bool found = false;
        bool visit[N];
        memset(visit, false, sizeof(visit));
        for (int j = 0; j < n; j++) {
            if (cur[j] < end[j] && s[j][cur[j]] == ch[i]) {
                cur[j]++;
                visit[j] = true;
                found = true;
            }
        }
        if (found) {
            str[dep] = ch[i];
            if (dfs(dep + 1)) return true;
            for (int j = 0; j < n; j++) {
                if (visit[j]) cur[j]--;
                if (cur[j] < 0) {
                    while (1);
                }
            }
        }
    }
    return false;
}

int IDAStar() {
    limit = *max_element(end, end + n);
    nextLimit = inf;
    memset(cur, 0, sizeof(cur));
    while (1) {
        if (dfs(0)) break;
        limit = nextLimit;
        nextLimit = inf;
    }    
    return limit;
}

int main() {
    for (int i = 0; i < 4; i++) {
        w[ch[i]] = i;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%s", s[i]), end[i] = strlen(s[i]);
        for (int i = 0; i < n; i++) {
        }
        printf("%d\n", IDAStar());
    }
    return 0;
}
