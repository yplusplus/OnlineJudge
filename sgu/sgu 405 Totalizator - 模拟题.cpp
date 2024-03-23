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
const int N = 111;
int n, m;
int ans[N];

int whoWin(int a, int b) {
    if(a == b) return 2;
    return a < b;
}

int calc(int teamA, int teamB, int guessA, int guessB) {
    int res = 0;
    if(whoWin(teamA, teamB) == whoWin(guessA, guessB)) res += 2;
    if(teamA + guessB == teamB + guessA) res += 3;
    res += teamA == guessA;
    res += teamB == guessB;
    return res;
}

int main() {
    while(cin >> n >> m) {
        memset(ans, 0, sizeof(ans));
        for(int i = 0; i < m; i++) {
            int teamA, teamB, guessA, guessB;
            cin >> teamA >> teamB;
            for(int j = 0; j < n; j++) {
                cin >> guessA >> guessB;
                ans[j] += calc(teamA, teamB, guessA, guessB);
            }
        }
        for(int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        puts("");
    }
    return 0;
}
