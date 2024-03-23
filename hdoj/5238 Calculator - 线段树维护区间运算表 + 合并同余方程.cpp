#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int mod[] = {7, 13, 17, 19};
const int N = 55555;
const int M = 20;
char op[50];
vector<string> ops;
int table[7][13][17][19];

int power_mod(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

struct Node {
    int val[M];
};

struct SegTree {
    int mod;
    Node node[N << 2];
    void PushUp(int p, int l, int r) {
        for (int i = 0; i < mod; i++) {
            node[p].val[i] = node[p << 1 | 1].val[node[p << 1].val[i]];
        }
    }
    void build(int p, int l, int r) {
        if (l == r) {
            const string & op = ops[l];
            int val = atoi(op.c_str() + 1);
            for (int i = 0; i < mod; i++) {
                if (op[0] == '+') node[p].val[i] = (i + val) % mod;
                else if (op[0] == '*') node[p].val[i] = (i * val) % mod;
                else node[p].val[i] = node[p].val[i] = power_mod(i, val, mod);
            }
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        PushUp(p, l, r);
    }
    void Modify(int p, int l, int r, int x) {
        if (l == r) {
            const string & op = ops[l];
            int val = atoi(op.c_str() + 1);
            for (int i = 0; i < mod; i++) {
                if (op[0] == '+') node[p].val[i] = (i + val) % mod;
                else if (op[0] == '*') node[p].val[i] = (i * val) % mod;
                else node[p].val[i] = power_mod(i, val, mod);
            }
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid) Modify(p << 1, l, mid, x);
        else Modify(p << 1 | 1, mid + 1, r, x);
        PushUp(p, l, r);
    }
} stree[4];

int main() {
    for (int i = 0; i < 29393; i++) {
        table[i % mod[0]][i % mod[1]][i % mod[2]][i % mod[3]] = i;
    }
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        ops.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%s", op);
            ops[i] = op;
        }
        for (int i = 0; i < 4; i++) {
            stree[i].mod = mod[i];
            stree[i].build(1, 0, n - 1);
        }
        printf("Case #%d:\n", Case++);
        for (int i = 0; i < m; i++) {
            int cmd, x;
            scanf("%d", &cmd);
            if (cmd == 1) {
                scanf("%d", &x);
                int a = stree[0].node[1].val[x % stree[0].mod];
                int b = stree[1].node[1].val[x % stree[1].mod];
                int c = stree[2].node[1].val[x % stree[2].mod];
                int d = stree[3].node[1].val[x % stree[3].mod];
                int ans = table[a][b][c][d];
                printf("%d\n", ans);
            } else {
                scanf("%d%s", &x, op);
                x--;
                ops[x] = op;
                for (int i = 0; i < 4; i++) stree[i].Modify(1, 0, n - 1, x);
            }
        }
    }
    return 0;
}
