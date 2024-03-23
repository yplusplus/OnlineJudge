#include <iostream>
using namespace std;

int main() {
    int x, y, z;
    while (cin >> x >> y >> z) {
        int score = x * 3 + y * 2 + z * 6;
        if (score < 60) {
            cout << "Exam was too hard." << endl;
        } else {
            cout << "I passed the exam." << endl;
        }
        cout << score << endl;
    }
    return 0;
}
