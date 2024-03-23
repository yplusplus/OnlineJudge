#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int M = 2;
int n;
int a[15];
double p;

class Mat {
    public:
        double val[M][M];
        Mat() {
            memset(val, 0, sizeof(val));
        }
        void toUnitMat() {
            for (int i = 0; i < M; i++) val[i][i] = 1;
        }
        Mat operator*(const Mat &x) {
            Mat res;
            for (int k = 0; k < M; k++) {
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < M; j++) {
                        res.val[i][j] += val[i][k] * x.val[k][j];
                    }
                }
            }
            return res;
        }
        Mat operator^(int b) {
            Mat res;
            Mat a = *this;
            res.toUnitMat();
            while (b) {
                if (b & 1) res = res * a;
                b >>= 1;
                a = a * a;
            }
            return res;
        }
};

int main() {
    while (~scanf("%d%lf", &n, &p)) {
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a + n);
        bool found = (a[0] == 1);
        for (int i = 1; i < n; i++) {
            found |= (a[i] == a[i - 1] + 1);
        }
        if (found) {
            puts("0.0000000");
            continue;
        }
        Mat ans, b;
        b.val[0][0] = 0, b.val[0][1] = 1 - p, b.val[1][0] = 1, b.val[1][1] = p;
        ans.val[0][1] = 1;
        int now = 1;
        for (int i = 0; i < n; i++) {
            int delta = a[i] - 1 - now;
            ans = ans * (b ^ delta);
            ans.val[0][0] = 0;
            ans.val[0][1] *= 1 - p;
            now = a[i] + 1;
        }
        printf("%.7f\n", ans.val[0][1]);
    }
    return 0;
}

