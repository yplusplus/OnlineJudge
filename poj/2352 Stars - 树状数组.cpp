#include "iostream"
#include "cstring"
using namespace std;
#define MAX 32005
#define lowbit(x) x & (-x)
int n, c[MAX], cnt[MAX];

void update(int x, int v) {
    for(int i = x; i <= MAX; i += lowbit(i)) c[i] += v;
}

int sum(int x) {
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) res += c[i];
    return res;
}

int main() {
    int x, y;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        int rank = sum(x + 1);
        cnt[rank]++;
        update(x + 1, 1);
    }
    for(int i = 0; i < n; i++)
        cout << cnt[i] << endl;
    return 0;
}