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
#define maxn 1050000
char s[maxn];
int slen, len;
int next[maxn];
int getnext() {
    int i = 1, j = 0, cnt = 0;
    next[1] = 0;
    while(i <= len) {
        if(j == 0 || s[i] == s[j]) {
            i++, j++, next[i] = j;
            if(next[i] == slen + 1) cnt++;
        } else j = next[j];
    }
    return cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", s + 1);
        slen = strlen(s + 1);
        s[slen+1] = '$';
        scanf("%s", s + slen + 2);
        len = strlen(s + 1);
        printf("%d\n", getnext());
    }
    return 0;
}
