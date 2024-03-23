#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef unsigned long long LL;

const int M = 200003;
const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

int sx, sy, ex, ey;
int n;

LL encode(int x, int y) { LL res = ((LL)x) << 32 | y; return res; }

struct Element {
    LL key;
    int value;
    int next;
};

struct HashMap {
    void clear() { tot = 0; memset(header, -1, sizeof(header)); }
    int hash(LL key) { return ((key ^ 1231124 | 3920 >> 3 ^ (11234)) % M + M) % M; }
    void set(LL key, int value) {
        int v = hash(key);
        for (int i = header[v]; i != -1; i = elements[i].next) {
            if (elements[i].key == key) {
                elements[i].value = value;
                return;
            }
        }
        elements[tot].key = key;
        elements[tot].value = value;
        elements[tot].next = header[v];
        header[v] = tot++;
    }
    int get(LL key) {
        int v = hash(key);
        for (int i = header[v]; i != -1; i = elements[i].next) {
            if (elements[i].key == key) {
                return elements[i].value;
            }
        }
        return 0;
    }

    Element *find(LL key) {
        int v = hash(key);
        for (int i = header[v]; i != -1; i = elements[i].next) {
            if (elements[i].key == key) {
                return &elements[i];
            }
        }
        return NULL;
    }

    int tot;
    Element elements[M];
    int header[M];
};

int que[M], head, tail;
HashMap steps;

int bfs() {
    head = tail = 0;
    que[tail++] = sx; que[tail++] = sy;
    steps.set(encode(sx, sy), 0);
    while (head < tail) {
        int x = que[head++]; int y = que[head++];
        int step = steps.get(encode(x, y));
        if (x == ex && y == ey) return step;
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            Element *p_element = steps.find(encode(nx, ny));
            if (p_element == NULL || p_element->value != -1) continue;
            p_element->value = step + 1;
            que[tail++] = nx; que[tail++] = ny;
        }
    }
    return -1;
}

void solve() {
    int ans = bfs();
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d%d%d", &sx, &sy, &ex, &ey)) {
        scanf("%d", &n);
        steps.clear();
        for (int i = 0, r, a, b; i < n; i++) {
            scanf("%d%d%d", &r, &a, &b);
            for (int j = a; j <= b; j++) {
                steps.set(encode(r, j), -1);
            }
        }
        solve();
    }
    return 0;
}
