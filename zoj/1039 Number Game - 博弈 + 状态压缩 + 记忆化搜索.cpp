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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 524287
int n, x[20];
int dp[MAX+10];
vector<int> vec;

void getmask(int &tmp, int &forbid, int x) {
    for(int i = x; i <= 20; i += x) {
        if(tmp & (1<<(i-2))) {
            tmp &= ~(1<<(i-2));
            forbid |= (1<<(i-2));
        }
    }
    for(int i = 2; i <= 20; i++) {
        if(forbid & (1<<(i-2)))
            for(int j = i + 1; j <= 20 - i; j++) {
                if((forbid & (1<<(j-2))) && (tmp & (1<<(i+j-2)))) {
                    tmp &= ~(1<<(i+j-2)), forbid |= (1<<(i-2));
                }
            }
    }
}

bool g(int mask, int forbid) {
    if(dp[mask] != -1) return dp[mask];
    for(int i = 2; i <= 20; i++) {
        if(mask & (1<<(i-2))) {
            int nmask = mask, nforbid = forbid;
            getmask(nmask, nforbid, i);
            if(!g(nmask, nforbid)) return dp[mask] = 1;
        }
    }
    return dp[mask] = 0;
}

void init() {
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    init();
    while(T--) {
        vec.clear();
        scanf("%d", &n);
        int mask = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            mask |= (1<<(x[i]-2));
        }
        int forbid = MAX & ~mask;
        for(int i = 0; i < n; i++) {
            int nmask = mask, nforbid = forbid;
            getmask(nmask, nforbid, x[i]);
            if(!g(nmask, nforbid)) vec.pb(x[i]);
        }
        printf("Scenario #%d:\n", Case++);
        if(vec.size()) {
            sort(vec.begin(), vec.end());
            printf("The winning moves are:");
            for(int i = 0; i < vec.size(); i++) printf(" %d", vec[i]);
            printf(".\n\n");
        } else printf("There is no winning move.\n\n");
    }
    return 0;
}
