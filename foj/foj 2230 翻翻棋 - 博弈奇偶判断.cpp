#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string row;
        int ax, ay, bx, by;
        for (int i = 0; i < 4; i++) {
            cin >> row;
            for (int j = 0; j < row.length(); j++) {
                if (row[j] == '.') ax = i, ay = j;
                if (row[j] == '*') bx = i, by = j;
            }
        }
        int t = abs(ax - bx) + abs(ay - by);
        cout << (t % 2 == 0 ? "Black" : "Red") << " win" << endl;
    }
    return 0;
}
