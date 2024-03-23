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
#define ull unsigned long long
#define maxn 256
const int MOD = 1000000007;
const int nn = 1 << 8;
int mask[10];
struct Mat {
    int val[maxn][maxn];
    void unit() {//µ¥Î»¾ØÕó
        zero();
        for(int i = 0; i < maxn; i++) val[i][i] = 1;
    }
    void zero() {//Áã¾ØÕó
        memset(val, 0, sizeof(val));
    }
}a, b, d[35];

Mat operator *(Mat a, Mat b) {//¾ØÕó³Ë·¨
    Mat tmp;
    tmp.zero();
    for(int k = 0; k < nn; k++) {
        for(int i = 0; i < nn; i++)
            if(a.val[i][k])
                for(int j = 0; j < nn; j++) {
                    if(!b.val[k][j]) continue;
                    ull res = (ull)a.val[i][k] * (ull)b.val[k][j];
                    res += tmp.val[i][j];
                    if(res >= MOD) res %= MOD;
                    tmp.val[i][j] = res;
                }
    }
    return tmp;
}

void init() {
    for(int i = 0; i < 8; i++) {
        mask[i] = (1 << i) | (1 << ((i + 1) % 8));
    }
    a.zero();
    for(int i = 0; i < nn; i++) {
        for(int j = 0; j < nn; j++) {
            bool flag = true;
            int mm = i ^ (nn - 1);
            for(int k = 0; k < 8; k++) {
                if((j & (1 << k))) {
                    if(mm & mask[k]) {
                        flag = false;
                        break;
                    } else mm |= mask[k];
                }
            }
            if(flag) a.val[i][mm]++;
        }
    }
    b.zero();
    for(int i = 0; i < nn; i++) {
        int mm = 0;
        bool flag = true;
        for(int j = 0; j < 8; j++) {
            if(i & (1 << j)) {
                if(mm & mask[j]) {
                    flag = false;
                    break;
                } else mm |= mask[j];
            }
        }
        if(flag) b.val[0][mm]++;
    }
}

int main() {
    int T, h, Case = 1;
    init();
    d[0] = a;
    for(int i = 1; i <= 30; i++)
        d[i] = d[i-1] * d[i-1];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &h);
        h--;
        Mat ans = b; 
        for(int i = 30; i >= 0 && h; i--) {
            if(h & (1 << i)) ans = ans * d[i], h ^= (1 << i);
        } 
        printf("Case %d: %d\n", Case++, ans.val[0][nn-1]);
    }
    return 0;
}

