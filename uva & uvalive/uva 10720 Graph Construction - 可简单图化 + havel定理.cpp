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

const int N = 11111;
int n;
int d[N];

bool solve() {
    for (int i = 0; i < n; i++) {
        sort(d + 1, d + n, greater<int>());
        int cnt = d[i];
        for (int j = i + 1; j < n && cnt; j++, cnt--)
            if (--d[j] < 0) return false;
        if (cnt) return false;
    }
    return true;
}

int main() {
    while (~scanf("%d", &n), n) {
        bool found = false;
        for (int i = 0; i < n; i++) { scanf("%d", &d[i]); }
        puts(!solve() ? "Not possible" : "Possible");
    }
    return 0;
}
