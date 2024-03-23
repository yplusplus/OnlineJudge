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
const int N = 10011;
int Prime[N], tot;
int n;
bool isSuperPrime[N];
int ans[N];
void init() {
    bool isPrime[N];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    tot = 1;
    for(int i = 2; i < N; i++) {
        if(isPrime[i]) {
            Prime[tot++] = i;
            for(int j = i * i; j < N; j += i) isPrime[j] = false;
        }
    }
    memcpy(isSuperPrime, isPrime, sizeof(isPrime));
    for(int i = 1; i < tot; i++) {
        if(!isPrime[i]) isSuperPrime[Prime[i]] = false;
    }
}

int main() {
    init();
    vector<int> vec[N];
    for(int i = 0; i <= 10000; i++) {
        ans[i] = 0;
        if(isSuperPrime[i]) {
            ans[i] = 1;
            vec[i].pb(i);
            continue;
        } else {
            int rec = -1;
            int tmp = inf;
            for(int j = 3; j * 2 <= i; j++) {
                if(ans[j] == 0 || ans[i-j] == 0) continue;
                if(tmp > ans[j] + ans[i-j]) {
                    rec = j;
                    tmp = ans[j] + ans[i-j];
                }
            }
            if(rec == -1) continue;
            ans[i] = tmp;
            for(int j = 0; j < vec[rec].size(); j++) {
                vec[i].pb(vec[rec][j]);
            }
            for(int j = 0; j < vec[i-rec].size(); j++) {
                vec[i].pb(vec[i-rec][j]);
            }
            sort(vec[i].begin(), vec[i].end());
            reverse(vec[i].begin(), vec[i].end());
        }
    }
    while(cin >> n) {
        cout << ans[n] << endl;
        for(int i = 0; i < ans[n]; i++) {
            printf("%d%c", vec[n][i], i == ans[n] - 1 ? '\n' : ' ');
        } 
    }
    return 0;
}
