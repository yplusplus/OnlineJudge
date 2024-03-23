#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 55555;
const int M = 16;
vector<PII> vec[N];

int n, m, q;
int block_sz;
int a[N];
LL ans[N];

inline int get_block_id(int x) { return x / block_sz; }

struct Query {
    int L, R, id;
    bool operator<(const Query &rhs) const {
        int l_block_id = get_block_id(L);
        int r_block_id = get_block_id(rhs.L);
        if (l_block_id != r_block_id) return l_block_id < r_block_id;
        return R < rhs.R;
    }
} query[N];

struct Node {
    int cnt, child[2];
    void clear() { cnt = child[0] = child[1] = 0; }
};

struct Trie {
    Node node[N * 16];
    int tot;
    void clear() { node[tot = 0].clear(); }
    void insert(int x) {
        int p = 0;
        for (int i = M - 1; i >= 0; i--) {
            int bit = x >> i & 1;
            if (node[p].child[bit] == 0) {
                node[p].child[bit] = ++tot;
                node[tot].clear();
            }
            p = node[p].child[bit];
            node[p].cnt++;
        }
    }
    LL query(int p, int x, int pos, bool e) {
        //cout << p << " " << x << " " << pos << " " << e << endl;
        if (!e) {
            return node[p].cnt;
        }
        if (pos == -1) return 0; 
        LL res = 0;
        for (int i = 0; i < 2; i++) {
            int bit = (x >> pos & 1) ^ i;
            int m_bit = (m >> pos & 1);
            if (bit < m_bit) continue;
            if (node[p].child[i])
                res += query(node[p].child[i], x, pos - 1, e && bit == m_bit);
        }
        return res;
    }
} small_trie, big_trie;

void dfs(int u, int fa, int cc) {
    a[u - 1] = cc;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == fa) continue;
        dfs(v, u, cc ^ vec[u][i].second);
    }
}

void solve() {
    sort(query, query + q);
    for (int i = 0; i < q; i++) {
        int j = i;
        int block_id = get_block_id(query[i].L);
        while (j + 1 < q && get_block_id(query[i].L) == get_block_id(query[j + 1].L)) j++;
        big_trie.clear();
        int p = (block_id + 1) * block_sz;
        LL sum = 0;
        for (int k = i; k <= j; k++) {
            while (p <= query[k].R) {
                sum += big_trie.query(0, a[p], M - 1, 1);
                big_trie.insert(a[p]);
                p++;
            }
            //cout << "sum = " << sum << endl;
            ans[query[k].id] = 0;
            small_trie.clear();
            ans[query[k].id] += sum;
            for (int z = query[k].L; z <= min(query[k].R, (block_id + 1) * block_sz - 1); z++) {
                ans[query[k].id] += small_trie.query(0, a[z], M - 1, 1);
                ans[query[k].id] += big_trie.query(0, a[z], M - 1, 1);
                small_trie.insert(a[z]);
            }
        }
        i = j;
    }
    for (int i = 0; i < q; i++) {
        printf("%lld\n", ans[i]);
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
        block_sz = sqrt(n);
        //cout << "block_sz = " << block_sz << endl;
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vec[a].push_back(make_pair(b, c));
            vec[b].push_back(make_pair(a, c));
        }
        dfs(1, 0, 0);
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &query[i].L, &query[i].R);
            query[i].L--;
            query[i].R--;
            //cout << query[i].L << " " << query[i].R << endl;
            query[i].id = i;
        }
        solve();
    }
    return 0;
}

