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

#define maxn 1000001
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int rank[maxn],height[maxn],sa[maxn];
int r[maxn];
int n;
int cmp(int *r,int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m) {
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) wc[i]=0;
    for(i=0;i<n;i++) wc[x[i]=r[i]]++;
    for(i=1;i<m;i++) wc[i]+=wc[i-1];
    for(i=n-1;i>=0;i--) sa[--wc[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p) {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) wc[i]=0;
        for(i=0;i<n;i++) wc[wv[i]]++;
        for(i=1;i<m;i++) wc[i]+=wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
void calheight(int *r,int *sa,int n) {
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
     for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}

bool check(int mid) {
    int minn = sa[1], maxx = sa[1];
    for(int i = 2; i <= n; i++) {
        if(height[i] >= mid) {
            minn = min(minn, sa[i]);
            maxx = max(maxx, sa[i]);
            if(maxx - minn >= mid) return true;
        } else minn = maxx = sa[i];
    }
    return false;
}

int main() {
    int a, b;
    while(~scanf("%d", &n), n) {
        n--;
        scanf("%d", &b);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a);
            r[i] = a - b + 100;
            b = a;
        }
        r[n] = 0;
        da(r, sa, n + 1, 256);
        calheight(r, sa, n);
        int l = 1, r = 2 * n;
        int ans = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(check(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        if(ans >= 4) cout << ans + 1 << endl;
        else cout << 0 << endl;
    }
    return 0;
}
