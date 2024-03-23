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
#define maxn 510
vector<int> vec;
int n, k;
int main() {
    while(cin >> n >> k) {
        vec.resize(n);
        for(int i = 0; i < n; i++) cin >> vec[i];
        sort(vec.begin(), vec.end());
        int cnt = 0;
        for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
            if(*it <= k) cnt++;
            else k += 2;
        }
        cout << k + cnt << endl;
    }
    return 0;
}
