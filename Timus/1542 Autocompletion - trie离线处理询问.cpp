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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
const int M = 15555;
const int kind = 26;
vector<int> vec[M];
int n, m;
int rank[N], weight[N];
char str[N][18], s[20];
int same[M];
struct Trie {
    int root, tot;
    struct Node {
        int child[kind], id;
        void init() {
            memset(child, 0, sizeof(child));
            id = 0;
        }
    } node[15 * M];
    void clear() {
        tot = root = 0;
        node[root].init();
    }
    void insert(char *str, int id) {
        int p = root;
        while (*str) {
            int idx = (*str) - 'a';
            if (!node[p].child[idx]) {
                node[p].child[idx] = ++tot;
                node[tot].init();
            }
            p = node[p].child[idx];
            str++;
        }
        if (node[p].id == 0) node[p].id = id;
        else same[id] = node[p].id;
    }
    void query(char *str, int id) {
        int p = root;
        while (*str) {
            int idx = (*str) - 'a';
            if (!node[p].child[idx]) break;
            p = node[p].child[idx];
            if (node[p].id > 0 && vec[node[p].id].size() < 10) vec[node[p].id].pb(id);
            str++;
        }
    }
} trie;

bool cmp(int a, int b) {
    if (weight[a] != weight[b]) return weight[a] > weight[b];
    return strcmp(str[a], str[b]) == -1;
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            rank[i] = i;
            scanf("%s%d", str[i], &weight[i]);
        }
        sort(rank + 1, rank + 1 + n, cmp);
        scanf("%d", &m);
        trie.clear();
        for (int i = 1; i <= m; i++) {
            same[i] = i;
            scanf("%s", s);
            trie.insert(s, i);
            vec[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            trie.query(str[rank[i]], rank[i]);
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < vec[same[i]].size(); j++) {
                puts(str[vec[same[i]][j]]);
            }
            if (i != m) puts("");
        }
    }
    return 0;
}
