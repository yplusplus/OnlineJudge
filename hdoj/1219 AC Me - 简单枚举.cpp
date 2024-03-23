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
int cnt[30];
char str[100050];
int main() {
    while(gets(str)) {
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(str);
        for(int i = 0; i < len; i++) {
            if(str[i] <= 'z' && str[i] >= 'a') {
                cnt[str[i] - 'a']++;
            }
        }
        for(int i = 0; i < 26; i++) {
            putchar('a' + i);
            printf(":%d\n", cnt[i]);
        }
        puts("");
    }
    return 0;
}
