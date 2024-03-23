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

int a[4];
int main() {
    int Case = 1;
    while(~scanf("%d", &a[0])) {
        for(int i = 1; i <= 3; i++) scanf("%d", &a[i]);
        sort(a, a + 4);
        printf("Case %d: %d\n", Case++, a[3] + a[2]);
    }
    return 0;
}
