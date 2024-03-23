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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int kind = 52;//���ӽ�����
const int maxn = 300;//�ܽ����
int root, tot;
int que[maxn];//�����Զ����Ķ���
int w[256];//�ַ���Ӧ��
struct Node {
    int child[kind], fail, id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = id = 0;
    }
} T[maxn];
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s, int id) {//���뵥��
    int p = root, index;
    while (*s) {
        index = w[*s];
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].id = id;//������Ŀ��Ҫ
}
void build_ac_auto() {
    int head = 0, tail = 0;
    que[tail++] = root;
    while (head < tail) {
        int u = que[head++];
        for (int i = 0; i < kind; i++) {
            if (T[u].child[i]) {
                int son = T[u].child[i];
                int p = T[u].fail;
                if(u) {
                    T[son].fail = T[p].child[i];
                    T[son].id += T[T[p].child[i]].id;
                }
                que[tail++] = son;
            } else {//trieͼ���趨����ڵ�
                int p = T[u].fail;
                T[u].child[i] = T[p].child[i];
            }
        }
    }
}

pii rec[555555];
char a[300], b[555555];
int main() {
    for(int i = 0; i < 26; i++) w[i+'a'] = i;
    for(int i = 0; i < 26; i++) w[i+'A'] = 26 + i; 
    while(~scanf("%s%s", a, b + 1)) {
        int alen = strlen(a), blen = strlen(b + 1);
        init();
        insert(a, 1);
        build_ac_auto();
        int p = 0, ans = 0, cur = 0;
        rec[0] = mp(-1, 0);
        for(int i = 1; i <= blen; i++) {
            p = T[p].child[w[b[i]]];
            rec[i] = mp(cur, p);
            cur = i;
            if(T[p].id) {
                ans++;
                for(int j = 0; j < alen; j++) {
                    cur = rec[cur].fi;
                }
                p = rec[cur].se;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
