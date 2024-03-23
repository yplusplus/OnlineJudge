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

bool isprime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int sum(int x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int dfs(int n) {
    if (isprime(n)) return sum(n);
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return dfs(i) + dfs(n / i);
    }
}

int n;
int main() {
    while (cin >> n, n) {
        ++n;
        while (true) {
            if (!isprime(n) && dfs(n) == sum(n)) {
                cout << n << endl;
                break;
            }
            n++;
        }
    }
    return 0;
}
