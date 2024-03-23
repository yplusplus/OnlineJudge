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
const int N = 22222;
int n, m;
int fa[N], val[N];
void init() {
    for (int i = 0; i < N; i++) {
        val[i] = 0;
        fa[i] = i;
    }
}

int find(int x) {
	if (x == fa[x]) return x;
	int t = fa[x];
    fa[x] = find(t);
    val[x] ^= val[t];
    return fa[x];
}

bool Union(int a, int b, int c) {
    //int v = val[a] ^ val[b];
    int ra = find(a);
    int rb = find(b);
    int v = val[a] ^ val[b];
    if (ra == rb) {
        return v == c;
    }
    if (ra == n) swap(ra, rb);
    fa[ra] = rb;
    val[ra] = v ^ c;
    return true;
}

int main() {
    int Case = 1;
    char buffer[100];
	while (~scanf("%d%d", &n, &m), n + m) {
        printf("Case %d:\n", Case++);
        init();
        int fact = 0;
        bool found = false;
        for (int num = 0; num < m; num++) {
            scanf("%s", buffer);
            if (buffer[0] == 'I') {
                fact++;
                gets(buffer);
                if (found) continue;
                int a, b, c;
                int ret = sscanf(buffer, "%d%d%d", &a, &b, &c);
                if (ret == 2) {
                    c = b;
                    b = n;
                }
                if (!Union(a, b, c)) {
                    printf("The first %d facts are conflicting.\n", fact);
                    found = true;
                }
            } else {
                map<int, int> cnt;
                int k, x;
                scanf("%d", &k);
                int ans = 0;
                for (int i = 0, x; i < k; i++) {
                    scanf("%d", &x);
                    cnt[find(x)]++;
                    ans ^= val[x];
                }
                if (found) continue;
                bool flag = true;
                for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it++) {
                    if (it->fi != n && it->se % 2 == 1) {
                        flag = false;
                        break;
                    }
                }
                if (flag) printf("%d\n", ans);
                else puts("I don't know.");
            }
        }
        puts("");
    }
    return 0;
}
