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

const int N = 11111;
struct Person {
    int v, id, c;
} person[N];

bool cmp(const Person &a, const Person &b) {
    if (a.v != b.v) return a.v < b.v;
    return a.id > b.id;
}

bool cmpId(const Person &a, const Person &b) {
    return a.id < b.id;
}

int p, n;

int bs(int sum, int n, int v) {
    int l = 0, r = min(sum / n, v);
    int res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (mid * n <= sum) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &p, &n);
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &person[i].v);
            person[i].id = i;
            sum += person[i].v;
        }
        if (sum < p) {
            puts("IMPOSSIBLE");
        } else {
            sort(person, person + n, cmp);
            int t = 0;
            for (int i = 0; i < n; i++) {
                int res = bs(p, n - i, person[i].v - t);
                t += res;
                p -= res * (n - i);
                person[i].c = t;
            }
            sort(person, person + n, cmpId);
            for (int i = 0; i < n; i++) {
                printf("%d%c", person[i].c, i == n - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
