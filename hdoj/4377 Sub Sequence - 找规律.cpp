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

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int m;
        m=(int)ceil(sqrt((double)n));
        int tmp=n/m;
        if (n%m!=0) tmp++;
        bool flag=false;
        if (tmp==m) {
            int idx=n-n/m*m;
            for (int i=idx; i>=1; i--) {
                if (flag) printf(" "); 
                else flag=true;
                printf("%d",i);
            }
            for (int i=1; i<=n/m; i++) {
                for (int j=m; j>=1; j--) {
                    if (flag) printf(" "); 
                    else flag=true;
                    printf("%d",idx+(i-1)*m+j);
                }
            }
            printf("\n");
        } else {
            int k=m-tmp;
            for (int i=1; i<=k; i++) {
                if (flag) printf(" "); 
                else flag=true;
                printf("%d",i);
            }
            int idx=n-n/m*m;
            if (idx==0) idx=m;
            for (int i=idx; i>=k+1; i--) {
                if (flag) printf(" "); 
                else flag=true;
                printf("%d",i);
            }
            int i;
            if (n%m==0) i=2,idx=0;
            else i=1;
            for (; i<=n/m; i++) {
                for (int j=m; j>=1; j--) {
                     if (flag) printf(" "); 
               else  flag=true;
                    printf("%d",idx+(i-1)*m+j);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
