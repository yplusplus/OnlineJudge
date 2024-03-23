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

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        char cmd[5];
        int x;
        stack<int> s;
        set<int> d;
        d.insert(0);
        d.insert(n + 1);
        while (m--) {
            scanf("%s", cmd);
            if (cmd[0] == 'D') {
                scanf("%d", &x);
                d.insert(x);
                s.push(x);
            } else if (cmd[0] == 'Q') {
                scanf("%d", &x);
                if (d.find(x) != d.end()) puts("0");
                else {
                    int t = n;
                    set<int>::iterator it = d.upper_bound(x);
                    t = *it - 1;
                    it--;
                    t -= *it;
                    cout << t << endl;
                }
            } else if (cmd[0] == 'R') {
                if (s.empty()) continue;
                x = s.top(), s.pop();
                d.erase(x);
            }
        }
    }
    return 0;
}

