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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 222222;
int n;
int main() {
    while(cin >> n) {
        priority_queue<pii> heap;
        string str;
        int x;
        for(int i = 2; i < n; i++) {
            cin >> str >> x;
            if(str == "d") heap.push(mp(-x, i));
            else {
                while(heap.size() >= x) heap.pop();
            }
        }
        cin >> str >> x;
        if(heap.size() < x) puts("-1");
        else {
            int ans = 0;
            vector<int> scheme;
            while(!heap.empty()) {
                ans -= heap.top().fi;
                scheme.pb(heap.top().se);
                heap.pop();
            }
            sort(scheme.begin(), scheme.end());
            cout << ans << endl;
            cout << scheme.size() << endl;
            for(int i = 0; i < scheme.size(); i++) {
                printf("%d%c", scheme[i], i == scheme.size() - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
