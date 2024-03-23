#include <iostream>
using namespace std;

const int N = 111;
int a[N];
int n, m;

void solve() {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    long long ave = sum / m;
    while (true) {
        bool found = false;
        sum = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > ave) {
                a[i] = ave;
                found = true;
            }
            sum += a[i];
        }
        if (!found) break;
        ave = sum / m;
    }
    cout << ave << endl;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        solve();
    }
    return 0;
}
