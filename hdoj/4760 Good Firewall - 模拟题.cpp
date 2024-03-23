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

struct IP {
    unsigned address, mask;
    void read(int type = 0) {
        unsigned a, b, c, d;
        if (type) scanf("%u.%u.%u.%u/%u", &a, &b, &c, &d, &mask);
        else scanf("%u.%u.%u.%u", &a, &b, &c, &d);
        address = (a << 24) + (b << 16) + (c << 8) + d;
    }
};

vector<IP> group[1111];
bool enable[1111];

bool check(const vector<IP> &group, const IP &src, const IP &dest) {
    bool f1 = false, f2 = false;
    for (int i = 0; i < group.size(); i++) {
        if ((src.address ^ group[i].address) < (1u << (32 - group[i].mask))) f1 = true;
        if ((dest.address ^ group[i].address) < (1u << (32 - group[i].mask))) f2 = true;
        if (f1 && f2) return true;
    }
    return false;
}

int main() {
    int tot = 0;
    char cmd[10];
    while (~scanf("%s", cmd)) {
        if (cmd[0] == 'E') {
            int group_id, number;
            scanf("%d%d", &group_id, &number);
            assert(group_id <= 1024);
            assert(number <= 15);
            enable[group_id] = true;
            for (int i = 0; i < number; i++) {
                IP subnet;
                subnet.read(1);
                group[group_id].pb(subnet);
            }
            tot = max(tot, group_id);
        } else if (cmd[0] == 'F') {
            IP src, dest;
            src.read(), dest.read();
            bool found = false;
            for (int i = 1; i <= tot; i++) {
                if (enable[i] && check(group[i], src, dest)) {
                    found = true;
                    break;
                }
            }
            puts(found ? "F" : "D");
        } else if (cmd[0] == 'D') {
            int group_id;
            scanf("%d", &group_id);
            enable[group_id] = false;
        }
    }
    return 0;
}
