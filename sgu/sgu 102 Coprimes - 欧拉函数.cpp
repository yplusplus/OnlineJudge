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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 10050
int phi[maxn], n;
void getphi() {
    memset(phi, 0, sizeof (phi));
    phi[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!phi[i]) {
            for (int j = i; j < maxn; j += i) {
                if (!phi[j])  phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int main() {
    getphi();
    while(~scanf("%d", &n)) {
        printf("%d\n", phi[n]);
    }
    return 0;
}
