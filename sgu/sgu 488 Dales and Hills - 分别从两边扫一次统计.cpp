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
const int N = 1111111;
int n;
int a[N], L[2][N], R[2][N];

//分别从两边扫一次即可
//大数据，用cin，cout会TLE
//数组用多少初始化多少

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < n; i++) {
            L[0][i] = L[1][i] = 0;
            R[0][i] = R[1][i] = 0;
        }
        for(int i = 1; i < n; i++) {
            if(a[i] > a[i-1]) {
                L[0][i] = L[0][i-1] + 1;
            } else if(a[i] < a[i-1]) {
                L[1][i] = L[1][i-1] + 1;
            }
        }
        int height = min(L[0][n-1], R[0][n-1]), depth = min(L[1][n-1], R[1][n-1]);
        for(int i = n - 2; i >= 0; i--) {
            if(a[i] > a[i + 1]) {
                R[0][i] = R[0][i+1] + 1;
            } else if(a[i] < a[i + 1]) {
                R[1][i] = R[1][i+1] + 1;
            }
            height = max(height, min(L[0][i], R[0][i]));
            depth = max(depth, min(L[1][i], R[1][i]));
        }
        printf("%d %d\n", height, depth);
    }
    return 0;
}
