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

int a[4][4] = {2, 3, 1, 1, 1, 2, 3, 1, 1, 1, 2, 3, 3, 1, 1, 2};
int b[4][4];
int c[4][4];
int main() {
    int T;
    scanf("%d", &T);
    bool flag = false;
    while(T--) {
        if(flag) puts("");
        else flag = true;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                scanf("%X", &b[i][j]);
        memset(c, 0, sizeof(c));
        for(int k = 0; k < 4; k++) {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    int tmp = b[k][j];
                    if(a[i][k] == 1) c[i][j] ^= tmp;
                    else if(a[i][k] == 2) {
                        tmp <<= 1; 
                        if(tmp > 255) tmp ^= 27;
                        c[i][j] ^= tmp;
                    } else if(a[i][k] == 3) {
                        tmp <<= 1;
                        if(tmp > 255) tmp ^= 27;
                        tmp ^= b[k][j];
                        c[i][j] ^= tmp;
                    }
                }
            }
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 3; j++) {
                printf("%02X ", (c[i][j] & 255));
            }
            printf("%02X\n", (c[i][3] & 255));
        }
    }
    return 0;
}
