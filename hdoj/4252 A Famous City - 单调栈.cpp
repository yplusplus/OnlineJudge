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
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

int main() {
    int x, n;
    int Case = 1;
    while(~scanf("%d", &n)) {
        stack<int> s;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            if(x == 0) {
                ans += s.size();
                while(!s.empty()) s.pop();
            } else if(s.empty()) s.push(x);
            else {
                while(!s.empty() && x < s.top()) s.pop(), ans++;
                if((s.empty()) || (!s.empty() && x > s.top())) s.push(x);
            }
        }
        printf("Case %d: %d\n", Case++, ans + s.size());
    }
    return 0;
}
