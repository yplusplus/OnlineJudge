#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 111111;
int n;

struct Exam {
    int r, e, l;
    bool operator<(const Exam & o) const {
        return e < o.e;
    }
} exam[N];

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d%d", &exam[i].r, &exam[i].e, &exam[i].l);
        sort(exam, exam + n);
        int cnt = 0;
        int now = 0;
        bool pass = true;
        for (int i = 0; i < n; i++) {
            cnt += exam[i].e - now;
            now = exam[i].e + exam[i].l;
            if (cnt < exam[i].r) {
                pass = false;
                break;
            }
            cnt -= exam[i].r;
        }
        printf("Case #%d: %s\n", Case++, pass ? "YES" : "NO");
    }
    return 0;
}
