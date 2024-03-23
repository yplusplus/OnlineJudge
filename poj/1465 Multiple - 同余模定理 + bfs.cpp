#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 5050
bool visit[maxn];
int n, m;
int x[15];
struct Node {
    int x;
    string s;
    Node(int _x, string _s) {
        x = _x, s = _s;
    }
    Node(){}
}que[maxn];
int head, tail;

void bfs() {
    memset(visit, false, sizeof(visit));
    head = tail = 0;
    que[tail++] = Node(0, "");
    while(head < tail) {
        Node now = que[head++];
        for(int i = 0; i < m; i++) {
            int xx = now.x * 10 + x[i];
            while(xx >= n) xx -= n;
            char ch = x[i] + '0';
            string ss = now.s + ch;
            if(xx == 0 && now.x != 0) {
                cout << ss << endl;
                return;
            }
            if(!visit[xx]) {
                visit[xx] = true;
                que[tail++] = Node(xx, ss);
            }
        }
    }
    printf("0\n");
}

int main() {
    while(~scanf("%d", &n)) {
        scanf("%d", &m);
        for(int i = 0; i < m; i++) scanf("%d", &x[i]);
        sort(x, x + m);
        if(n == 0) {
            printf("0\n");
            continue;
        } else bfs();
    }
    return 0;
}
