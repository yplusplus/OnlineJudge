#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int n, m;
int s, t;
int visit[1<<21];

int bfs() {
    int all = (1 << m) - 1;
    queue<int> que;
    memset(visit, -1, sizeof(visit));
    visit[0] = 0;
    que.push(0);
    while(!que.empty()) {
        int fingernail = que.front();
        que.pop();
        if(fingernail == all) return visit[fingernail];
        for(int i = 0; i < m + n; i++) {
            int clipper = (s >> i) & all;
            int newFingernail = fingernail | clipper;
            if(visit[newFingernail] != -1) continue;
            else {
                que.push(newFingernail);
                visit[newFingernail] = visit[fingernail] + 1;
            }
        }
        for(int i = 0; i < m + n; i++) {
            int clipper = (t >> i) & all;
            int newFingernail = fingernail | clipper;
            if(visit[newFingernail] != -1) continue;
            else {
                que.push(newFingernail);
                visit[newFingernail] = visit[fingernail] + 1;
            }
        }
    }
    return -1;
}

int main() {
    string str;
    while(cin >> n) {
        cin >> str >> m;
        s = t = 0;
        for(int i = 0; i < n; i++) {
            if(str[i] == '*') {
                s |= (1 << i);
                t |= (1 << (n - 1 - i));
            }
        }
        if(s == 0) {
            puts("-1");
            continue;
        }
        s <<= (m - 1);
        t <<= (m - 1);
        cout << bfs() << endl;
    }
    return 0;
}
