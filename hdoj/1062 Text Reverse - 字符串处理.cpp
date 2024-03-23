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

const int N = 1111;
void solve(char s[]) {
    int len = strlen(s);
    s[len++] = '\n';
    int p = 0;
    char word[N];
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ' || s[i] == '\n') {
            if (p) {
                reverse(word, word + p);
                word[p++] = '\0';
                printf("%s", word);
                p = 0;
            }
            putchar(s[i]);
        } else {
            word[p++] = s[i];
        }
    }
}

int main() {
    int T;
    char str[N];
    cin >> T;
    getchar();
    while (T--) {
        gets(str);
        solve(str);
    } 
    return 0;
}

