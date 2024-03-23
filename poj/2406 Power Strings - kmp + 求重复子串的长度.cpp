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
#define maxn 1000050
char s[maxn];
int next[maxn];
void getnext() {
    int i = 0, j = -1;
    next[i] = j;
    int len = strlen(s);
    while(i < len) {
        if(j == -1 || s[i] == s[j]) i++, j++, next[i] = j;
        else j = next[j];
    }
}

int main() {
    while(~scanf("%s", s)) {
        if(strcmp(s, ".") == 0) break;
        getnext();
        int len = strlen(s);
        if(len % (len - next[len]) == 0) printf("%d\n", len / (len - next[len]));
        else printf("1\n");
    }
    return 0;
}
