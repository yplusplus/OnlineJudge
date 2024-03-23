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
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

string s;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int tab = 0, space = 0;
        while(1) {
            getline(cin, s);
            if(s == "##") break;
            int len = s.length();
            bool flag = true;
            for(int i = len - 1; i >= 0; i--) {
                if(s[i] != ' ' && s[i] != '\t') flag = false;
                if(s[i] == '\t') tab++;
                if(flag && s[i] == ' ') space++;
                if(flag && s[i] == '\t') space += 4;
            }
        }
        printf("%d tab(s) replaced\n", tab);
        printf("%d trailing space(s) removed\n", space);
    }
    return 0;
}
