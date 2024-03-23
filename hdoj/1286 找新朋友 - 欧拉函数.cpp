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
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 33000

int p[maxn], tot;

int eular(int n){
    int sum = n;
    for (int i = 2; i * i <= n ; i ++){
        if(n % i == 0){
            sum = sum / i * (i - 1);
            while(n % i == 0) n/=i;
        }
    }
    if (n>1) sum = sum / n * (n - 1);
    return sum;
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        cout << eular(n) << endl;
    }
    return 0;
}
