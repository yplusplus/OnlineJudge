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
int visit[1111];
ll A, alpha, beta, gamma, M, k;

//一开始想简单了，循环节不一定从1开始！！！！
int main() {
    while(cin >> A >> alpha >> beta >> gamma >> M >> k) {
        if(k == 0) {
            cout << A << endl;
            continue;
        }
        memset(visit, -1, sizeof(visit));
        ll x = A, ans;
        int circleLen = -1;
        for(int i = 1; 1; i++) {
            x = (alpha * x * x + beta * x + gamma) % M;
            if(i == k) {
                ans = x;
                k = 0;
                break;
            }
            if(visit[x] != -1) {
                circleLen = i - visit[x];
                k = (k - i) % circleLen;
                ans = x;
                break;
            } else visit[x] = i;
        }
        for(int i = 0; i < k; i++) {
            ans = (alpha * ans * ans + beta * ans + gamma) % M;
        }
        cout << ans << endl;
    }
    return 0;
}
