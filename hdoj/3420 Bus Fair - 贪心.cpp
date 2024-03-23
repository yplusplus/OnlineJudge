#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1111;
int a[N];

int main() {
    int n, x;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, a[i] * (n - i));
        }
        cout << ans << endl;
    }
    return 0;
}
