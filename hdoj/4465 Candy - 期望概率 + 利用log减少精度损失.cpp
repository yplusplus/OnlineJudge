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
const int N = 444444;
int n;
double p;
double Log[N];
int main() {
    for (int i = 1; i < N; i++) Log[i] = log(i * 1.0);
    int Case = 1;
    while (~scanf("%d", &n)) {
        scanf("%lf", &p);
        if (p < 1e-6 || (1 - p) < 1e-6) {
            printf("Case %d: %d\n", Case++, n);
            continue;
        }
        double ans = 0.0;
        double q = 1 - p;
        double pn_1 = (n + 1) * log(p);
        double qn_1 = (n + 1) * log(q);
        double tmp = 0;
        for (int i = n; i < 2 * n; i++) {
            double t1 = tmp + pn_1 + (i - n) * log(q) + Log[2 * n - i];
            double t2 = tmp + qn_1 + (i - n) * log(p) + Log[2 * n - i];
            tmp += Log[i + 1] - Log[i + 1 - n];
            ans += exp(t1) + exp(t2);
        }
        printf("Case %d: %.8f\n", Case++, ans);
    }
    return 0;
}

