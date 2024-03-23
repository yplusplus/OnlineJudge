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

bool dp[30][30];
string s;
int main() {
    memset(dp, false, sizeof(dp));
    while(cin >> s) {
        if(s[0] == '0') {
            for(int k = 0; k < 26; k++)
                for(int i = 0; i < 26; i++)
                    for(int j = 0; j < 26; j++)
                        dp[i][j] |= dp[i][j] | (dp[i][k] & dp[k][j]);
            if(dp['b'-'a']['m'-'a']) puts("Yes.");
            else puts("No.");
            memset(dp, false, sizeof(dp));
        } else {
            dp[s[0]-'a'][s[s.length()-1]-'a'] = true;
        }
    }
    return 0;
}
