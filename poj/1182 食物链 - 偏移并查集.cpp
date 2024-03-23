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

const int N = 55555;
int fa[N];
int offset[N];
int n, m;
void init() {
    for (int i = 0; i < N; i++) {
        fa[i] = i;
        offset[i] = 0;
    }
}

int find(int x) {
    if (x == fa[x]) return x;
    int t = fa[x];
    fa[x] = find(t);
    offset[x] = (offset[x] + offset[t]) % 3;
    return fa[x];
}

bool Union(int a, int b, int c) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) {
        return (offset[a] - offset[b] + 3) % 3 == c; 
    }
    fa[ra] = rb;
    offset[ra] = (3 + offset[b] + c - offset[a]) % 3;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    int counter = 0;
    int a, b, c;
    init();
    while (m--) {
        scanf("%d%d%d", &c, &a, &b);
        if (a > n || a < 1 || b > n || b < 1) {
            counter++;
        } else counter += !Union(a, b, c - 1);
    }
    printf("%d\n", counter);
    return 0;
}

