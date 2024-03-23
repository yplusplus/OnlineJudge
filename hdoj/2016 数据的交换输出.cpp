#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
const int inf = 1 << 30;
int val[maxn];
int n;

int main() {
    while(~scanf("%d", &n)) {
        if(!n) break;
        int tmp = inf, idx = -1;
        for(int i = 0; i < n; i++) {
            cin >> val[i];
            if(tmp > val[i]) tmp = val[idx = i];
        }
        swap(val[0], val[idx]);
        cout << val[0];
        for(int i = 1; i < n; i++) cout << " " << val[i];
        cout << endl; 
    }
    return 0;
}
