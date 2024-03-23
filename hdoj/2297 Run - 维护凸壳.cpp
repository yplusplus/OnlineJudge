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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
struct Person {
    int p, v;
    void read() { scanf("%d%d", &p, &v); }
    bool operator < (const Person &x) const {
        if (p != x.p) return p > x.p;
        return v > x.v;
    }
} person[N];
int n;
int maxV[N];
int que[N], head, tail;

bool check(int a, int b, int c) {
    ll t1 = (person[a].p - person[b].p) * (person[c].v - person[a].v);
    ll t2 = (person[a].p - person[c].p) * (person[b].v - person[a].v);
    return t2 <= t1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        maxV[0] = 0;
        for (int i = 1; i <= n; i++) {
            person[i].read();
        }
        sort(person + 1, person + 1 + n);
        for (int i = 1; i <= n; i++) {
            maxV[i] = max(maxV[i - 1], person[i].v);
        }
        tail = 0;
        for (int i = 1; i <= n; i++) {
            if (person[i].v < maxV[i - 1]) continue;
            if (tail > 1 && check(que[tail - 2], que[tail - 1], i)) tail--;
            que[tail++] = i;
        }
        int ans = tail;
        printf("%d\n", ans);
    }
    return 0;
}
