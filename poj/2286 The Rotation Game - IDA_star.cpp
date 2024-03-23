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
const int N = 24;
int limit;
int a[N], b[N];
int c[] = {6, 7, 8, 11, 12, 15, 16, 17};
int d[][7] = {
    {0,2,6,11,15,20,22},
    {1,3,8,12,17,21,23},
    {10,9,8,7,6,5,4},
    {19,18,17,16,15,14,13},
    {23,21,17,12,8,3,1},
    {22,20,15,11,6,2,0},
    {13,14,15,16,17,18,19},
    {4,5,6,7,8,9,10}
};
char ansStr[1111], str[1111];

int g(int mask) {
    int cnt = 8;
    for (int i = 0; i < 8; i++) {
        if (mask >> c[i] & 1) cnt--;
    }
    return cnt;
}

int getMask(int b[]) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        res |= (b[i] << i);
    }
    return res;
}

int go(int now, int k) {
    for (int i = 0; i < N; i++) {
        b[i] = now >> i & 1;
    }
    swap(b[d[k][0]], b[d[k][6]]);
    for (int i = 0; i < 5; i++) {
        swap(b[d[k][i]], b[d[k][i + 1]]);
    }
    return getMask(b);
}

bool dfs(int now, int dep) {
    if (dep + g(now) > limit) return false;
    if (g(now) == 0) {
        str[dep] = 0;
        return true;
    }
    for (int i = 0; i < 8; i++) {
        int next = go(now, i);
        str[dep] = 'A' + i;
        if (dfs(next, dep + 1)) return true;
    }
    return false;
}

void gao() {
    int ansNum = -1;
    bool ok = false;
    for (limit = 0; ; limit++) {
        for (int i = 1; i <= 3; i++) {
            for (int j = 0; j < N; j++) {
                b[j] = a[j] == i;
            }
            int start = getMask(b);
            if (dfs(start, 0)) {
                ok = true;
                if (ansNum == -1 || strlen(ansStr) > strlen(str) || (strlen(ansStr) == strlen(str) && strcmp(str, ansStr) < 0)) {
                    strcpy(ansStr, str);
                    ansNum = i;
                }
            }
        }
        if (ok) break;
    }
    if (strlen(ansStr) == 0) {
        puts("No moves needed");
    } else {
        puts(ansStr);
    }
    printf("%d\n", ansNum);
}

int main() {
    while (scanf("%d", &a[0]), a[0]) {
        for (int i = 1; i < N; i++) {
            scanf("%d", &a[i]);
        }
        gao();
    }
    return 0;
}
