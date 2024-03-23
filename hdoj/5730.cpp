#include <iostream>
#include <cstring>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <algorithm>

using namespace std;

#define rep(i, L, R) for(int i=L; i<R; ++i)
typedef complex<double> C;
typedef long long LL;
const double PI(acos(-1));
const int N = 1 << 18;
struct FFT {
    C a[N], b[N];
    long long ans[N];
    void bit_reverse_swap(C *a, int n){
        for(int i=1, j=n>>1; i<n-1; i++){
            if(i<j) swap(a[i], a[j]);   //error-prone
            int k=n>>1;
            for(;j>=k; j-=k, k>>=1);
            j+=k;
        }
    }

    void fft(C *a, int n, int t){
        bit_reverse_swap(a, n); //error-prone
        for(int i=2; i<=n; i<<=1){
            C wi(cos(t*2*PI/i), sin(t*2*PI/i));
            for(int j=0; j<n; j+=i){
                C w(1);
                for(int k=j, h=i>>1; k<j+h; k++){
                    C u=a[k], t=a[k+h];
                    a[k]=u+w*t;
                    a[k+h]=u-w*t;
                    w*=wi; 
                }
            }
        }
        if(t==-1) rep(i, 0, n) a[i]/=n; //error-prone
    }

    void multiply(C *a, C *b, int n){
        fft(a, n, 1), fft(b, n, 1);
        rep(i, 0, n) a[i]*=b[i];
        fft(a, n, -1);
        rep(i, 0, n) ans[i]=(LL)(a[i].real()+0.5);  //error-prone
    }

    void multiply(int *x, int *y, int n) {
        for (int i = 0; i < n; i++) a[i] = C(x[i]);
        for (int i = 0; i < n; i++) b[i] = C(y[i]); 
        multiply(a, b, n);
    }
      
    int expand(int n){
        int i=0;
        for(; n>1<<i; i++);
        return 1<<i;    //error-prone
    }
}fft;

int v[N];
int a[N], b[N];
long long dp[N];

void add(long long &a, long long b) { b %= 313; a += b; a %= 313; }

void solve(int l, int r) {
    if (l == r) {
        add(dp[l], v[l]);
        return;
    }
    int mid = (l + r) / 2;
    solve(l, mid);
    int len = fft.expand(mid - l + 1 + r - l);
    memset(a, 0, sizeof(a[0]) * len);
    memset(b, 0, sizeof(b[0]) * len);
    for (int i = l; i <= mid; i++) { a[i - l] = dp[i]; }
    for (int i = 1; i <= r - l; i++) { b[i - 1] = v[i]; }
    fft.multiply(a, b, len);
    for (int i = mid + 1; i <= r; i++) {
        add(dp[i], fft.ans[i - l - 1]);
    }
    solve(mid + 1, r);
}

int main() {
    int n;
    while (~scanf("%d", &n), n) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            v[i] %= 313;
        }
        memset(dp, 0, sizeof(dp));
        solve(1, n);
        printf("%d\n", (int)dp[n]);
    }
}
