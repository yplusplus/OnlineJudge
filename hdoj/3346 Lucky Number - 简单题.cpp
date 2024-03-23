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
int n;
int sum, sum2;

void func(int x) {
    sum = sum2 = 0;
    while(x) {
        int tmp = x % 10;
        sum += tmp;
        sum2 += tmp * tmp;
        x /= 10;
    }
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        func(n);
        if(n % 8 == 0 || sum % 8 == 0 || sum2 % 8 == 0) cout << "Lucky number!" << endl;
        else cout << "What a pity!" << endl;
    }    
    return 0;
}
