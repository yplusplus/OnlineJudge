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

string s;
int cnt[10];
bool dp[66666][20];
int mask[10];
pii pre[66666][20];

void dfs(int curMask, int r) {
    int preMask = pre[curMask][r].fi, preR = pre[curMask][r].se;
    if(preMask != -1) {
        dfs(preMask, preR);
        int delta = curMask - preMask;
        for(int i = 0; i < 10; i++)
            if(mask[i] == delta && cnt[i]) putchar(i + '0');
    } else {
        putchar(r + '0');
        //if(r == 0) cout << "***" << endl;
    }
}

int main() {
    while(cin >> s) {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < s.length(); i++) {
            cnt[s[i] - '0']++;
        }
        //for(int i = 0; i < 10; i++) cout << i << " " << cnt[i] << endl;
        mask[0] = 1;
        for(int i = 1; i <= 10; i++) mask[i] = mask[i-1] * (cnt[i-1] + 1);
        int maskSize = 0;
        for(int i = 0; i < 10; i++) {
            maskSize += cnt[i] * mask[i];
            //cout << i << " " << cnt[i] << " " << mask[i] << endl;
        }
        //cout << maskSize << endl;
        memset(dp, false, sizeof(dp));
        for(int i = 1; i < 10; i++) {
            if(cnt[i]) {
                dp[mask[i]][i] = true;
                pre[mask[i]][i] = mp(-1, -1);
            }
        }
        for(int m = 1; m < maskSize; m++) {
            for(int i = 0; i < 17; i++) {
                if(!dp[m][i]) continue;
                for(int j = 0; j < 10; j++) {
                    int k = m % mask[j + 1] / mask[j];
                    if(k >= cnt[j]) continue;
                    int mm = m + mask[j];
                    dp[mm][(i * 10 + j) % 17] = true;
                    pre[mm][(i * 10 + j) % 17] = mp(m, i);
                    //cout << "****" << endl;
                    //cout << m << " " << i << " " << j << " " << k << endl;
                    //cout << mm << " " << (i * 10 + j) % 17 << endl;
                }
            }
        }
        if(!dp[maskSize][0]) cout << -1 << endl;
        else {
            dfs(maskSize, 0);
            puts("");
        }
    }
    return 0;
}
