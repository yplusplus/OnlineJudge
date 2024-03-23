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

const int N = 1111111;
int mx[N];
int sum[N];
int n;
char cmd[5];
int a[N], b[N], atail, btail;
int main() {
    sum[0] = 0;
    mx[0] = -(1 << 30);
    while (~scanf("%d", &n)) {
        atail = btail = 0;
        for (int i = 0, x; i < n; i++) {
            scanf("%s", cmd);
            if (cmd[0] == 'I') {
                scanf("%d", &x);
                a[++atail] = x;
                sum[atail] = sum[atail - 1] + x;
                mx[atail] = max(sum[atail], mx[atail - 1]);
            } else if (cmd[0] == 'Q') {
                scanf("%d", &x);
                printf("%d\n", mx[x]);
            } else if (cmd[0] == 'L') {
                if (atail == 0) continue;
                b[++btail] = a[atail];
                atail--;
            } else if (cmd[0] == 'R') {
                if (btail == 0) continue;
                x = b[btail--];
                a[++atail] = x;
                sum[atail] = sum[atail - 1] + x;
                mx[atail] = max(sum[atail], mx[atail - 1]);
            } else if (cmd[0] == 'D') {
                atail--;
            }
        }
    }
    return 0;
}

