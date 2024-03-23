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
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

map<string, int> mp;
string s;
int main() {
    mp["I"] = 1;
    mp["II"] = 2;
    mp["III"] = 3;
    mp["IV"] = 4;
    mp["V"] = 5;
    mp["VI"] = 6;
    mp["VII"] = 7;
    mp["VIII"] = 8;
    mp["IX"] = 9;
    mp["X"] = 10;
    mp["XI"] = 11;
    mp["XII"] = 12;
    int Case = 1;
    while(cin >> s) {
        printf("Case %d: %d\n", Case++, mp[s]);
    }
    return 0;
}
