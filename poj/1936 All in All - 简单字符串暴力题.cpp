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
#define maxn 100050
char s[maxn], t[maxn];

bool solve() {
    int slen = strlen(s), tlen = strlen(t);
    if(slen > tlen) return false;
    int i = 0, j = 0;
    while(1) {
        if(i == slen) return true;
        else if(j == tlen) return false;
        if(s[i] == t[j]) i++, j++;
        else j++;
    }
}

int main() {
    while(~scanf("%s%s", s, t)) {
        if(solve()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
