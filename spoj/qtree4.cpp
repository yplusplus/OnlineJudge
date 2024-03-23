#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define mp make_pair
const int N = 100010;
const int NN = 2 * N;

vector<pair<int, int> > vec[N];

int weight[NN];
int heavy_edge;

int n;
int lson[NN], rson[NN];
int mx[NN];
bool del[N << 2];
int cnt[NN];
int color[NN];
int tot, heap_tot;
int edge_tot;

struct Edge {
    int u, v, w, next; 
} et[N << 2];
int eh[NN];

void add(int u, int v, int w) {
    Edge e = {u, v, w, eh[u]};
    et[edge_tot] = e;
    eh[u] = edge_tot++;
}

void addedge(int u, int v, int w) {
    //printf("(%d, %d) = %d\n", u, v, w);
    add(u, v, w);
    add(v, u, w);
}

void rebuild(int u, int fa) {
    int cc = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first, w = vec[u][i].second;
        if (v == fa) continue;
        if (cc == 0) {
            addedge(u, v, w);
            cc = u;
        } else {
            int k = ++tot;
            addedge(cc, k, 0);
            addedge(k, v, w);
            cc = k;
        }
        rebuild(v, u);
    }
}

priority_queue<pair<int, int> > hp[NN][2];
vector<pair<pair<int, int>, int> > heapids[NN];

void find_heavy_edge(int u, int fa, int ct) {
    cnt[u] = 1;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (del[i] || v == fa) continue;
        find_heavy_edge(v, u, ct);
        cnt[u] += cnt[v];
        if (heavy_edge == 0 || max(ct - cnt[et[heavy_edge].v], cnt[et[heavy_edge].v]) > max(ct - cnt[v], cnt[v])) {
            //cout << "****" << u << " " << v << endl;
            weight[heap_tot] = et[i].w;
            heavy_edge = i;
        }
    }
}

void dfs2(int u, int fa, int w, int heap_id, int idx) {
    if (u <= n) {
        hp[heap_id][idx].push(mp(w, u));
        heapids[u].push_back(mp(mp(heap_id, idx), w));
        //cout << "###" << heap_id << " " << idx << " " << u << " " << w << endl;
    }
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (del[i] || v == fa) continue;
        dfs2(v, u, w + et[i].w, heap_id, idx);
    }
}

void update(int heap_id) {
    while (!hp[heap_id][0].empty() && color[hp[heap_id][0].top().second]) {
        hp[heap_id][0].pop();
    }
    while (!hp[heap_id][1].empty() && color[hp[heap_id][1].top().second]) {
        hp[heap_id][1].pop();
    }
    mx[heap_id] = 0;
    if (!hp[heap_id][0].empty() && !hp[heap_id][1].empty()) {
        mx[heap_id] = hp[heap_id][0].top().first + hp[heap_id][1].top().first + weight[heap_id];
    }
    if (lson) mx[heap_id] = max(mx[heap_id], mx[lson[heap_id]]);
    if (rson) mx[heap_id] = max(mx[heap_id], mx[rson[heap_id]]);
    //cout << "mx = " << heap_id << " " << mx[heap_id] << endl;
}

int dfs(int u, int fa, int ct) {
    //cout << u << " " << fa << " " << ct << endl;
    //getchar();
    if (ct <= 1) return 0;
    // find heavy-edge
    heavy_edge = 0;
    int heap_id = ++heap_tot;
    find_heavy_edge(u, fa, ct);
    int x = et[heavy_edge].u;
    int y = et[heavy_edge].v;
    //cout << x << " " << y << endl;
    dfs2(x, y, 0, heap_id, 0);
    dfs2(y, x, 0, heap_id, 1);
    del[heavy_edge] = del[heavy_edge ^ 1] = true;
    int xct = ct - cnt[y];
    int yct = cnt[y];
    lson[heap_id] = dfs(x, y, xct);
    rson[heap_id] = dfs(y, x, yct);
    update(heap_id);
    return heap_id;
}

void solve() {
    edge_tot = 0;
    for (int i = 1; i <= 2 * n; i++) eh[i] = -1;
    tot = n;
    rebuild(1, 0);
    heap_tot = 0;
    dfs(1, 0, tot);

    int q;
    scanf("%d", &q);
    char cmd[10];
    int x;
    int white = n;
    for (int i = 0; i < q; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            if (white == 0) {
                puts("They have disappeared.");
            } else if (white == 1) {
                puts("0");
            } else {
                printf("%d\n", mx[1]);
            }
        } else {
            scanf("%d", &x);
            if (color[x]) {
                white++;
                color[x] = 0;
                for (int i = heapids[x].size() - 1; i >= 0; i--) {
                    int id = heapids[x][i].first.first;
                    int idx = heapids[x][i].first.second;
                    int w = heapids[x][i].second;
                    hp[id][idx].push(mp(w, x));
                    update(id);
                }
            } else {
                white--;
                color[x] = 1;
                for (int i = heapids[x].size() - 1; i >= 0; i--) {
                    int id = heapids[x][i].first.first;
                    //int idx = heapids[x][i].first.second;
                    //int w = heapids[x][i].second;
                    //hp[id][idx].push(mp(w, x));
                    update(id);
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        vec[a].push_back(mp(b, c));
        vec[b].push_back(mp(a, c));
    }

    solve();
    return 0;
}
