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

string s, t;
int main() {
    while(cin >> s >> t) {
        int bulls = 0, cows = 0;
        for(int i = 0; i < 4; i++) {
            if(s[i] == t[i]) bulls++;
            for(int j = 0; j < 4; j++) {
                if(i == j) continue;
                if(s[i] == t[j]) cows++;
            }
        }
        cout << bulls << " " << cows << endl;
    }
    return 0;
}
