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
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

int num[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int cnt[] = {0, 0, 1, 7, 4, 2, 6, 8};
int n;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        string b = "";
        scanf("%d", &n);
        int res = n / 7 + ((n % 7) ? 1 : 0);
        if(res == 1) {
            printf("%d", cnt[n]);
        } else {
            bool flag = 1;
            if(n == 10) {
                printf("22");
                flag = false;
            }
            int a = 1;
            while(flag) {
                int nn = res - 1;
                int tmp = nn * 6 + num[a];
                int delta = n - tmp;
                if(delta <= nn && delta >= 0) {
                    printf("%d", a);
                    for(int i = 0; i < res - 1 - delta; i++) printf("0");
                    for(int i = 0; i < delta; i++) printf("8");
                    break;
                }
                a++;
            }
        }
        if(n & 1) {
            b += '7';
            for(int tmp = n - 3, i = 0; i < tmp / 2; i++) b += '1';
        } else {
            for(int i = 0; i < (n >> 1); i++) b += '1';
        }
        cout << " " << b << endl;
    }
    return 0;
}
